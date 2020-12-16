#pragma once

#include "declarations.hpp"

#include <cmath>
#include <stdexcept>

namespace dce {
    namespace metrics {

        enum class metric_type {
            L1,
            L2,
            Hamming
        };

        float L1_distance(const fvector& query, const fvector &dataset) {
            if (query.size() != dataset.size()) {
                throw std::runtime_error("Vectors size not equal");
            }
            float result = 0.0f;
            for (int i = 0; i < query.size(); i++) {
                float val = query[i] - dataset[i];
                if (val < 0) {
                    val = 0 - val;
                }
                result += val;
            }

            return result;
        }

        float L2_distance(const fvector &query, const fvector &dataset) {
            if (query.size() != dataset.size()) {
                throw std::runtime_error("Vectors size not equal");
            }

            float sum = 0.0f;

            for (int i = 0; i < query.size(); ++i) {
                sum += std::pow((query[i] - dataset[i]), 2);
            }

            return std::pow(sum, 0.5);
        }

        float hamming_distance(const fvector &query, const fvector &dataset) {
            if (query.size() != dataset.size()) {
                throw std::runtime_error("Vectors size not equal");
            }

            size_t vec_size = query.size();
            float distance = 0.0f;

            for (int i = 0; i < vec_size; ++i) {
                if (query[i] != dataset[i]) {
                    distance++;
                }
            }

            return distance / vec_size;
        }
    }
}