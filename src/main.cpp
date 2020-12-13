#include <iostream>
#include "input_generator.hpp"

int main() {
    dce::input_generator gen;

    gen.set_lenght(1024);
    gen.set_count(2014);
    gen.set_start(5);
    gen.set_end(6);

    dce::fmatrix data = gen.generate();

    for (const auto &el_i : data) {
        for (const auto &el_j : el_i) {
            std::cout << el_j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout<<"[INFO]: Matrix count: "<<data.size()<<std::endl;
    std::cout<<"[INFO]: Matrix item lenght: "<<data.at(0).size()<<std::endl;

    return 0;
}
