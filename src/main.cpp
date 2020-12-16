#include <iostream>

#include "csv_reader.hpp"
#include "input_generator.hpp"
#include "log4dce.hpp"
#include "seq_engine.hpp"
#include "calculation_functions.hpp"
#include "settings.hpp"
#include "basic_json_reader.hpp"

int main(int argc, char **argv) {
    dce::log4dce *logger = dce::log4dce::get_root();
    dce::fmatrix query, dataset, out;

    try {
        dce::settings settings;
        settings.parse_args(argc, argv);

        if (settings.get_command_value(dce::settings::commands::query_csv) == dce::settings::values::empty &&
            settings.get_command_value(dce::settings::commands::dataset_csv) == dce::settings::values::empty) {

            dce::json_reader reader;
            reader.read("cfg/input_generator_config.json");

            std::cout<<"[INFO]: "<<"vectors_count: "<<reader.get_value("vectors_count")<<std::endl;
            std::cout<<"[INFO]: "<<"vector_lenght: "<<reader.get_value("vector_lenght")<<std::endl;
            std::cout<<"[INFO]: "<<"start: "<<reader.get_value("start")<<std::endl;
            std::cout<<"[INFO]: "<<"end: "<<reader.get_value("end")<<std::endl;

            dce::input_generator generator;
            generator.set_count(reader.get_value("vectors_count"));
            generator.set_lenght(reader.get_value("vector_lenght"));
            generator.set_start(reader.get_value("start"));
            generator.set_end(reader.get_value("end"));

            query = generator.generate();
            dataset = generator.generate();
        } else {
            dce::csv_reader reader;
            query = reader.read(settings.get_command_value(dce::settings::commands::query_csv));
            dataset = reader.read(settings.get_command_value(dce::settings::commands::dataset_csv));
        }

        if(settings.get_command_value(dce::settings::commands::seq) == dce::settings::values::on) {
            dce::seq_engine engine;
            out = engine.run(query, dataset, dce::metrics::L1_distance);
        }
    } catch (std::runtime_error &er) {
        std::cout << "[EXCEPTION]: " << er.what() << std::endl;
        logger->error(er.what());
    }

    for(const auto& el_i : out) {
        for(const auto& el_j : el_i) {
            std::cout<<el_j<<' ';
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    return 0;
}
