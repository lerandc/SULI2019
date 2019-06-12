#include <iostream>
#include <math.h>

__global__
void add(int n, float *x, float *y){
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = gridDim.x * blockDim.x;
    for (int i = index; i < n; i+=stride) y[i] = x[i] + y[i];
}

int main(void){
    int N = 1<<20; // 1M elemenets
    std::cout << N << std::endl;

    float *x, *y;
    cudaMallocManaged(&x, N*sizeof(float));
    cudaMallocManaged(&y, N*sizeof(float));

    for (int i = 0; i < N; i++){
        x[i] = 1.0f;
        y[i] = 2.0f;
    }

    ///Run kernel, rounding number of blocks up in case N is not multiple of blocksize
    int blockSize = 256;
    int numBlocks = (N+blockSize-1) / blockSize;
    add <<< numBlocks, 256 >>> (N,x,y);

    //wait for synchro
    cudaDeviceSynchronize();

    float maxError = 0.0f;
    for (int i = 0; i < N; i++) maxError = fmax(maxError, fabs(y[i]-3.0f));

    std::cout << "max error: " << maxError << std::endl;

    cudaFree(x);
    cudaFree(y);
    return 0;
}