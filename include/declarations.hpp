#pragma once

#include <vector>
#include <functional>

namespace dce {
    using fvector = std::vector<float>;
    using fmatrix = std::vector<fvector>;

    using metric_function = std::function<float(size_t, fvector::const_iterator, fvector::const_iterator)>;
} //  dce: distance calculation engine
