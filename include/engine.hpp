#pragma once

#include "declarations.hpp"

namespace dce {
    class engine {
    public:
        fmatrix run(const fmatrix& query, const fmatrix& dataset, metric_function callback);
    };
}