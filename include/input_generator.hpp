#pragma once

#include "declarations.hpp"

#include <random>

namespace dce {
    class input_generator {
    public:
        input_generator()
        : start_(-100)
        , end_(100)
        , count_(1024)
        , lenght_(512)
        {
        }

        ~input_generator() = default;

    public:
        inline void set_start(int start) noexcept      { start_ = start;   }
        inline void set_end(int end) noexcept          { end_ = end;       }
        inline void set_count(size_t count) noexcept   { count_ = count;   }
        inline void set_lenght(size_t lenght) noexcept { lenght_ = lenght; }
    public:
        fmatrix generate() noexcept;

    private:
        int start_;
        int end_;
        size_t count_;
        size_t lenght_;
    };

    fmatrix input_generator::generate() noexcept {
        std::random_device rand_device_;
        std::mt19937 gen(rand_device_());
        std::uniform_int_distribution<> distrib(start_, end_);

        fmatrix out_matrix;
        fvector temp_vec;

        for(int i = 0; i < count_; ++i) {
            for(int j = 0; j < lenght_; ++j) {
                temp_vec.push_back(distrib(gen));
            }
            out_matrix.push_back(temp_vec);
            temp_vec.clear();
        }

        return out_matrix;
    }
}