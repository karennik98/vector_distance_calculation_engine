#include <cuda.h>
#include <cuda_runtime.h>

namespace dce {
        namespace metrics {
            namespace cuda {
                namespace hamming {

                template<typename TValue>
                __global__ void distance(size_t size, TValue *vec_1, TValue *vec_2, TValue *distance) {
                    int index = threadIdx.x + blockIdx.x * blockDim.x;

                    TValue count = 0.0f;

                    if (vec_1[index] != vec_2[index]) {
                        count++;
                    }

                    *distance = count / size;
                }

                template<typename TValue, typename TVectorIter>
                TValue cuda_distance(size_t size, TVectorIter iter1, TVectorIter iter2) {
                    TValue* host_vec_1, host_vec_2, value;
                    host_vec_1 = (TValue *)malloc(size);
                    host_vec_2 = (TValue *)malloc(size);
                    value = (TValue *)malloc(sizeof(TValue));


                    TValue *device_vec_1, device_vec_2, distance;
                    cudaMalloc((void **) &device_vec_1, size);
                    cudaMalloc((void **) &device_vec_1, size);
                    cudaMalloc((void **) &distance, sizeof(TValue));

                    for (int i = 0; i < size; ++i) {
                        host_vec_1[i] = iter1[i];
                        host_vec_2[i] = iter2[i];
                    }

                    // Copy inputs to device
                    cudaMemcpy(device_vec_1, host_vec_1, size, cudaMemcpyHostToDevice);
                    cudaMemcpy(device_vec_2, host_vec_2, size, cudaMemcpyHostToDevice);

                    int THREADS_PER_BLOCK = 512;

                    distance < TValue ><<<size /
                                          THREADS_PER_BLOCK, THREADS_PER_BLOCK>>>(size, device_vec_1, device_vec_2, distance);

                    cudaMemcpy(value, distance, sizeof(TValue), cudaMemcpyDeviceToHost);


                    free(host_vec_1);
                    free(host_vec_2);
                    free(value);

                    cudaFree(device_vec_1);
                    cudaFree(device_vec_2);
                    cudaFree(distance);

                    return *value;
                }
            }
        }
    }
}