#include <iostream>

#include "csv_reader.hpp"

static const std::string file_path = "/home/karennik98/rau/parallel_programming/vector_distance_calculation_engine/csv_files/vector_example.csv";
int main() {
    dce::fmatrix data;
    try {
        dce::csv_reader reader;
        data = reader.read(file_path);
        } catch (std::exception& ex) {
        std::cout<<"[INFO]: Exception: "<< ex.what()<<std::endl;
    }

    for(const auto& el_i : data) {
        for (const auto& el_j : el_i) {
            std::cout<<el_j<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    return 0;
}
