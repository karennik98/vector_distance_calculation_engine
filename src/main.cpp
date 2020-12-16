#include <iostream>
#include "input_generator.hpp"
#include "log4dce.hpp"
#include "seq_engine.hpp"
#include "calculation_functions.hpp"
#include "settings.hpp"

int main(int argc, char **argv) {
    dce::settings set;
    try {
        set.parse_args(argc, argv);
    } catch (std::runtime_error& er) {
        std::cout<<"[ERROR]: "<<er.what()<<std::endl;
        exit(0);
    }
    std::cout << "[INFO]: " << dce::settings::commands::help << " " << set.get_command_value(dce::settings::commands::help) << std::endl;
    std::cout << "[INFO]: " << dce::settings::commands::mpi << " " << set.get_command_value(dce::settings::commands::mpi) << std::endl;
    std::cout << "[INFO]: " << dce::settings::commands::cuda << " " << set.get_command_value(dce::settings::commands::cuda) << std::endl;
    std::cout << "[INFO]: " << dce::settings::commands::seq << " " << set.get_command_value(dce::settings::commands::seq) << std::endl;
    std::cout << "[INFO]: " << dce::settings::commands::multi << " " << set.get_command_value(dce::settings::commands::multi) << std::endl;
    std::cout << "[INFO]: " << dce::settings::commands::dataset_csv << " " << set.get_command_value(dce::settings::commands::dataset_csv) << std::endl;
    std::cout << "[INFO]: " << dce::settings::commands::query_csv << " " << set.get_command_value(dce::settings::commands::query_csv) << std::endl;

    return 0;
}
