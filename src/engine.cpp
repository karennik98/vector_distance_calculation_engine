#include "engine.hpp"

#include <stdexcept>
#include <iostream>

namespace dce {
    fmatrix engine::run(const fmatrix &query, const fmatrix &dataset, metric_function callback) {
        fmatrix distance_matrix;
        size_t vec_size = query.size();
        for (int i = 0; i < vec_size; ++i) {
            fvector temp_vec;
            for (int j = 0; j < vec_size; ++j) {
                temp_vec.push_back(callback(query[i].size(), std::begin(query[i]), std::begin(dataset[j])));
            }
            distance_matrix.push_back(temp_vec);
            temp_vec.clear();
        }
        return distance_matrix;
    }
}
