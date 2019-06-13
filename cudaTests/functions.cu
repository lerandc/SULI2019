#include <iostream>
#include <math.h>
#include "reductions.cuh"
#include <chrono>

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
    }
}


void trial1(int N){
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
        float hx[N], hy[N], hz[N], hq[1];
        
        for (int i = 0; i < N; i++){
            hx[i] = 1.0f;
            hz[i] = 0.0f;
            hy[i] = 2.0f;
        }
        hq[0] = 0.0f;
        
        //std::cout << "stop 1" << std::endl;
        cudaMemcpy(x,&hx,N*sizeof(float),cudaMemcpyHostToDevice);
        cudaMemcpy(y,&hy,N*sizeof(float),cudaMemcpyHostToDevice);
        cudaMemcpy(z,&hz,N*sizeof(float),cudaMemcpyHostToDevice);
        cudaMemcpy(q,&hq,1*sizeof(float),cudaMemcpyHostToDevice);
        
        //std::cout << "stop 2" << std::endl;
        ///Run kernel, rounding number of blocks up in case N is not multiple of blocksize
        int blockSize = 256;
        int numBlocks = (N+blockSize-1) / blockSize;
        elementWiseMultiply <<< numBlocks, 256 >>> (N,x,y,z);
        
        //wait for synchro
        cudaDeviceSynchronize();
        
        reduction <<<  numBlocks, 256 >>> (N,z,q);
        
        cudaDeviceSynchronize();
        
        //std::cout << "stop 3" << std::endl;
        cudaMemcpy(hx,x,N*sizeof(float),cudaMemcpyDeviceToHost);
        cudaMemcpy(hy,y,N*sizeof(float),cudaMemcpyDeviceToHost);
        cudaMemcpy(hz,z,N*sizeof(float),cudaMemcpyDeviceToHost);
        cudaMemcpy(hq,q,1*sizeof(float),cudaMemcpyDeviceToHost);
        
        std::cout << hz[0] << std::endl;
        
        //std::cout << "stop 4" << std::endl;
        cudaFree(x);
        cudaFree(y);
        cudaFree(q);
        cudaFree(z);
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
    for(auto j = 0; j < 11; j++){
        auto start = std::chrono::high_resolution_clock::now();
        trial1(N);
        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = stop - start;
        std::cout << "Trial 1, test " << j << " elapsed time: " << elapsed.count() << " s\n";
        if(j > 0) trial1_time += elapsed.count(); //ignore startup trial
    }
    trial1_time /= 10;
    std::cout << "Average for trial 1: " << trial1_time << std::endl;
    std::cout << "------------------------" << std::endl;
    
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