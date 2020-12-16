#include "seq_engine.hpp"

#include <stdexcept>

namespace dce {
    fmatrix seq_engine::run(const fmatrix &query, const fmatrix &dataset, metric_function func) {
        fmatrix distance_matrix;
        size_t vec_size = query.size();
        for (int i = 0; i < vec_size; ++i) {
            fvector temp_vec;
            for (int j = 0; j < vec_size; ++j) {
                temp_vec.push_back(func(query[i], dataset[j]));
            }
            distance_matrix.push_back(temp_vec);
            temp_vec.clear();
        }
        return distance_matrix;
    }
}
