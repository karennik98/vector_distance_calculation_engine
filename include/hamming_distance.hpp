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
                                                 iter2 + i * chunk));
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
        }
    }
}