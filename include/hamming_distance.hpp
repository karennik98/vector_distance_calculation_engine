#pragma once

#include <cmath>
#include <stdexcept>
#include <thread>
#include <future>
#include <numeric>

namespace dce {
    namespace metrics {
        namespace hamming {
            template<typename TValue, typename TVectorIter>
            TValue sequential_distance(size_t size, TVectorIter iter1, TVectorIter iter2) {
                TValue distance = 0.0f;

                for (int i = 0; i < size; ++i) {
                    if (iter1[i] != iter2[i]) {
                        distance++;
                    }
                }

                return distance / size;
            }

            template<typename TValue, typename TVectorIter>
            TValue parallel_distance(size_t size, TVectorIter iter1, TVectorIter iter2) {
                size_t threads = std::thread::hardware_concurrency();

                if (threads > size) {
                    threads = size;
                }

                const size_t chunk = size / threads;
                const size_t tail = size - threads * chunk;

                std::vector <std::future<TValue>> pool;
                pool.reserve(threads + (tail > 0 ? 1 : 0));

                for (size_t i = 0; i < threads; ++i) {
                    pool.emplace_back(std::async(std::launch::async,
                                                 sequential_distance<TValue, TVectorIter>,
                                                 chunk,
                                                 iter1 + i * chunk,
                                                 iter1 + i * chunk));
                }

                if (tail > 0) {
                    pool.emplace_back(std::async(std::launch::async,
                                                 sequential_distance<TValue, TVectorIter>,
                                                 tail,
                                                 iter1 + threads * chunk,
                                                 iter2 + threads * chunk));
                }

                TValue hamming_distance = 0;
                for (auto &f : pool) {
                    hamming_distance += f.get();
                }

                return hamming_distance;
            }

            template<typename TValue, typename TVectorIter>
            TValue cuda_with_thrust_distance(size_t size, TVectorIter iter1, TVectorIter iter2) {
//                thrust::device_vector<double> dv1 = v1;
//                thrust::device_vector<double> dv2 = v2;
//                auto begin = thrust::make_zip_iterator(thrust::make_tuple(
//                        dv1.begin(), dv2.begin()));
//                auto end   = thrust::make_zip_iterator(thrust::make_tuple(
//                        dv1.end(),   dv2.end()  ));
//                const auto l1 = [](const thrust::tuple<double,double>& arg) {
//                    return fabs(thrust::get<0>(arg) - thrust::get<1>(arg));
//                }
//                const auto add = [](double a, double b) { return a+b; }
//
//                return thrust::transform_reduce(first, last, l1, 0.0, add);
            }

//            template<typename TValue>
//            __global__ void distance(size_t size, TValue* vec_1, TValue* vec_2, TValue* distance) {
//                int index = threadIdx.x + blockIdx.x * blockDim.x;
//
//                TValue count = 0.0f;
//
//                if (vec_1[index] != vec_2[index]) {
//                    count++;
//                }
//
//                distance = count / size;

//            }

            template<typename TValue, typename TVectorIter>
            TValue cuda_distance(size_t size, TVectorIter iter1, TVectorIter iter2) {
//                TValue* host_vec_1 = new TValue[size];
//                TValue* host_vec_2 = new TValue[size];
//
//                TValue* device_vec_1, device_vec_2;
//                TValue* distance;
//
//                cudaMalloc((void **)&device_vec_1, size);
//                cudaMalloc((void **)&device_vec_1, size);
//                cudaMalloc((void **)&distance, sizeof(TValue));
//
//                for(int i = 0; i < size; ++i) {
//                    host_vec_1[i] = iter1[i];
//                    host_vec_2[i] = iter2[i];
//                }
//
//                // Copy inputs to device
//                cudaMemcpy(device_vec_1, host_vec_1, size, cudaMemcpyHostToDevice);
//                cudaMemcpy(device_vec_2, host_vec_2, size, cudaMemcpyHostToDevice);
//
//                distance<TValue>()


            }

            template<typename TValue, typename TVectorIter>
            TValue mpi_distance(size_t size, TVectorIter iter1, TVectorIter iter2) {

            }
        }
    }
}