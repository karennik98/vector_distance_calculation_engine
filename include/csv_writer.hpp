#pragma once

#include "declarations.hpp"

#include <fstream>

namespace dce {
    class csv_writer {
    public:
        csv_writer() = default;
        ~csv_writer() {
            file_.close();
        };

    public:
        void write(const std::string& file, const fmatrix& data);

    private:
        std::ofstream file_;
        const std::string separator_=",";
    };
}