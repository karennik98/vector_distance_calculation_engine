#pragma once

#include "iengine.hpp"
#include "declarations.hpp"

namespace dce {
//    class seq_engine : public iengine {
//    public:
//        virtual fmatrix run(const fmatrix& query, const fmatrix& dataset, metric_function func) override;
//    };

    class seq_engine {
    public:
        fmatrix run(const fmatrix& query, const fmatrix& dataset, metric_function func);
    };
}