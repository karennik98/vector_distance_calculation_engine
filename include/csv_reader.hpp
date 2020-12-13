#pragma once

#include "declarations.hpp"

#include <vector>
#include <fstream>

namespace dce {
    class csv_reader {
    public:
        csv_reader() = default;
        ~csv_reader() = default;

    public:
        fmatrix read(const std::string& file);
        
    private:
        void open(const std::string& file);
    private:
        std::ifstream file_;
    };
} //  dce: distance calculation engine

