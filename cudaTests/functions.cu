#include <iostream>
#include <math.h>
#include "reductions.cuh"
#include <chrono>
#include <random>

__global__
void elementWiseMultiply(int n, float *x, float *y, float *z){
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < n) z[index] = x[index]*y[index];
}

__global__
void reduction(int n, float*x, float*y){
    int idx = threadIdx.x + blockDim.x*blockIdx.x;
    if (idx < n){
        atomicAdd(&y[0], x[idx]);
    }
}

__global__
void reduceMultiply(int n, float*x, float*y, float *z){
    int idx = threadIdx.x + blockDim.x*blockIdx.x;
    if (idx < n){
        atomicAdd(&z[0], x[idx]*y[idx]);
        if(idx == n-1) x[idx] = 10;
    }
}

__global__ void DPC_numerator_reduce(const float* psiIntensity_ds,
									const float* q_coord,
									float* numerator,
									const size_t N){
		int idx = threadIdx.x + blockDim.x * blockIdx.x;
		if (idx < N){
			atomicAdd(&numerator[0], psiIntensity_ds[idx]*q_coord[idx]);
		}
}

__global__ void DPC_denominator_reduce(const float* psiIntensity_ds,
									float* denominator,
									const size_t N){
	int idx = threadIdx.x + blockDim.x * blockIdx.x;
	if (idx < N){
		atomicAdd(&denominator[0], psiIntensity_ds[idx]);
	}										   
}

void trial1(const int N){
    for(auto j = 0; j < 100; j++){
         // 1M elemenets
        //std::cout << N << std::endl;
        //std::cout << "stop 0" << std::endl;
        float *x, *y, *z, *q;
        cudaMallocManaged(&x, N*sizeof(float));
        cudaMallocManaged(&y, N*sizeof(float));
        cudaMallocManaged(&q, 1*sizeof(float));
        cudaMallocManaged(&z, N*sizeof(float));
        
        //std::cout << "stop 1" << std::endl;
        float *hx = new float[N];
        float *hy = new float[N];
        float *hz = new float[N];
        float *hq = new float[N];
        
        for (int i = 0; i < N; i++){
            hx[i] = 1.0f;
            hz[i] = 0.0f;
            hy[i] = 2.0f;
        }
        hq[0] = 0.0f;
        
        //std::cout << "stop 1" << std::endl;
        cudaMemcpy(x,&hx[0],N*sizeof(float),cudaMemcpyHostToDevice);
        cudaMemcpy(y,&hy[0],N*sizeof(float),cudaMemcpyHostToDevice);
        cudaMemcpy(z,&hz[0],N*sizeof(float),cudaMemcpyHostToDevice);
        cudaMemcpy(q,&hq[0],1*sizeof(float),cudaMemcpyHostToDevice);
        
        //std::cout << "stop 2" << std::endl;
        ///Run kernel, rounding number of blocks up in case N is not multiple of blocksize
        int blockSize = 256;
        int numBlocks = (N+blockSize-1) / blockSize;
        //elementWiseMultiply <<< numBlocks, 256 >>> (N,x,y,z);
        
        //wait for synchro
        //cudaDeviceSynchronize();
        
        reduceMultiply <<<  numBlocks, 256 >>> (N,x,y,q);
        cudaError_t err = cudaGetLastError();
        if (err != cudaSuccess) 
            printf("Error: %s\n", cudaGetErrorString(err));
        cudaDeviceSynchronize();
        
        //std::cout << "dq: " << q[0] << std::endl;
        //std::cout << "stop 3" << std::endl;
        cudaMemcpy(&hx[0],x,N*sizeof(float),cudaMemcpyDeviceToHost);
        cudaMemcpy(&hy[0],y,N*sizeof(float),cudaMemcpyDeviceToHost);
        cudaMemcpy(&hz[0],z,N*sizeof(float),cudaMemcpyDeviceToHost);
        cudaMemcpy(&hq[0],q,1*sizeof(float),cudaMemcpyDeviceToHost);
        
        //std::cout << "hq: " << hq[0] << std::endl;
        //std::cout << hq[0] << std::endl;
        //std::cout << hx[N-1] << std::endl;
        
        //std::cout << "stop 4" << std::endl;
        cudaFree(x);
        cudaFree(y);
        cudaFree(q);
        cudaFree(z);

        delete [] hx;
        delete [] hy;
        delete [] hz;
        delete [] hq;

    }
}

void trial2(int N){
    for(auto i = 0; i < 100; i++){
        //std::cout << N << std::endl;
        
        float *x, *y, *z, *q;
        cudaMallocManaged(&x, N*sizeof(float));
        cudaMallocManaged(&y, N*sizeof(float));
        cudaMallocManaged(&q, 1*sizeof(float));
        cudaMallocManaged(&z, N*sizeof(float));
        
        for (int i = 0; i < N; i++){
            x[i] = 1.0f;
            z[i] = 0.0f;
            y[i] = 2.0f;
        }
        q[0] = 0.0f;
        
        ///Run kernel, rounding number of blocks up in case N is not multiple of blocksize
        int blockSize = 256;
        int numBlocks = (N+blockSize-1) / blockSize;
        reduceMultiply <<< numBlocks, 256 >>> (N,x,y,q);
        
        cudaDeviceSynchronize();
        
        cudaFree(x);
        cudaFree(y);
        cudaFree(q);
        cudaFree(z);
    }
    
}

int main(void){
    int N = 512;
    double trial1_time = 0.0;
    for(auto j = 0; j < 1; j++){
        auto start = std::chrono::high_resolution_clock::now();
        trial1(N);
        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = stop - start;
        std::cout << "Trial 1, test " << j << " elapsed time: " << elapsed.count() << " s\n";
        if(j > 0) trial1_time += elapsed.count(); //ignore startup trial
    }
    trial1_time /= 10;
    //std::cout << "Average for trial 1: " << trial1_time << std::endl;
	//std::cout << "------------------------" << std::endl;
	

	std::random_device rd;
    std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(0, 1000);

	float qxa[N];
	for(auto i = 0; i < N; i++) qxa[i] = i;
	
	float psi[N];
	for(auto i = 0; i < N; i++) psi[i] = dist(e2)/1000;

	//calculate DPC analogue on CPU side

	//numerator
	float num = 0;
	for(auto i = 0; i < N; i++) num += qxa[i]*psi[i];
	
	//denominator
	float den = 0;
	for(auto i = 0; i < N; i++) den += psi[i];

	//DPC
	std::cout << "CPU DPC_CoM    :" << num/den << std::endl;
	std::cout << "CPU numerator  :" << num << std::endl;
	std::cout << "CPU denominator:" << den << std::endl;
	std::cout << "------------------------" << std::endl;


	//calculate DPC analogue on GPU side

	//allocate variables
	float *qxa_d;
	float *psi_d;
	float *num_d;
	float *den_d;
	cudaMallocManaged(&qxa_d,N*sizeof(float));
	cudaMallocManaged(&psi_d,N*sizeof(float));
	cudaMallocManaged(&num_d,1*sizeof(float));
	cudaMallocManaged(&den_d,1*sizeof(float));

	//initialize variables
	float *zero = new float[1];
	zero[0] = 0.0;
	cudaMemcpy(qxa_d,&qxa[0],N*sizeof(float),cudaMemcpyHostToDevice);
	cudaMemcpy(psi_d,&psi[0],N*sizeof(float),cudaMemcpyHostToDevice);
	cudaMemcpy(num_d,&zero[0],1*sizeof(float),cudaMemcpyHostToDevice);
	cudaMemcpy(den_d,&zero[0],1*sizeof(float),cudaMemcpyHostToDevice);

	DPC_numerator_reduce <<< 2, 256 >>> (psi_d,qxa_d,num_d,N);
	DPC_denominator_reduce <<< 2, 256 >>> (psi_d,den_d,N);

	float DPC_gpu = num_d[0] / den_d[0];
	std::cout << "GPU DPC_CoM    :" << DPC_gpu << std::endl;
	std::cout << "GPU numerator  :" << num_d[0] << std::endl;
	std::cout << "GPU denominator:" << den_d[0] << std::endl;

	cudaFree(qxa_d);
	cudaFree(psi_d);
	cudaFree(num_d);
	cudaFree(den_d);
	free(zero);

    
    return 0;
}



    //for (int i = 0; i < N; i++) std::cout << x[i] << ' '  << y[i] << ' ' << z[i] << std::endl;
    
    /*
    unsigned int bytes = N * sizeof(float);
    
    float *d_idata = NULL;
    float *d_odata = NULL;
    
    float *h_idata = (float *) malloc(bytes);
    
    for (int i=0; i<N; i++){
        h_idata[i] = x[i];
        //std::cout << x[i] << std::endl;
    }
    float *h_odata = (float *) malloc(numBlocks*sizeof(float));
    cudaMemcpy(d_idata, h_idata, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_odata, h_idata, numBlocks*sizeof(float), cudaMemcpyHostToDevice);
    

    blockSize = 32;
    numBlocks = (N+blockSize-1) / blockSize;
    cudaMalloc((void **) &d_idata, bytes);
    cudaMalloc((void **) &d_odata, numBlocks*sizeof(float));
    
    reduce(N,32,32, d_idata, d_odata);
    //std::cout << d_odata[0] << std::endl;
    float result = 0;
    cudaMemcpy(h_odata, d_odata, numBlocks*sizeof(float), cudaMemcpyDeviceToHost);
    for (int i=0; i<numBlocks; i++){
        result += h_odata[i];
    }

    std::cout << h_odata[0] << std::endl;
    std::cout << result << std::endl;
    */