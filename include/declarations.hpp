#pragma once

#include <vector>
#include <functional>

namespace dce {
    using fvector = std::vector<float>;
    using fmatrix = std::vector<fvector>;
    using metric_function = std::function<float(const fvector&, const fvector&)>;
} //  dce: distance calculation engine
