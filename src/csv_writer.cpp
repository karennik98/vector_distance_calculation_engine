#include "csv_writer.hpp"

namespace dce {
    void csv_writer::write(const std::string &file, const fmatrix &data) {
        file_.open(file);
        if(!file_.is_open()) {
            throw std::runtime_error("Cant open file for write");
        }

        for(int i = 0; i < data.size(); ++i) {
            for(int j = 0; j < data[i].size(); ++j) {
                if(j == data[i].size() - 1) {
                    file_<<data[i][j]<<std::endl;
                } else {
                    file_ << data[i][j] << separator_;
                }
            }
        }

        file_.close();
    }
}