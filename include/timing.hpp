#pragma once

#include <string>

namespace dce
{
    namespace timing
    {
        void tic() noexcept;
        float toc() noexcept;
        std::string now() noexcept;
    }
}
