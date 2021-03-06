#include <iostream>

#include "csv_reader.hpp"
#include "csv_writer.hpp"
#include "input_generator.hpp"
#include "log4dce.hpp"
#include "engine.hpp"
#include "l1_distance.hpp"
#include "l2_distance.hpp"
#include "hamming_distance.hpp"
#include "settings.hpp"
#include "basic_json_reader.hpp"
#include "timing.hpp"

#include "cuda_hamming_distance.cuh"

void print_into_terminal(const dce::fmatrix& data) {
    for(const auto& el_i : data) {
        for(const auto& el_j : el_i) {
            std::cout<<el_j<<' ';
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

void print_help() noexcept {
    std::string msg = "Usage: dce [arguments] [value]\n"
    "\n"
    "Arguments:\n"
    "-print			Print output on <csv> file or <terminal>. Default on terminal\n"
    "-seq			Run sequential calculation engine <on>\n"
    "-multi			Run sequential multithreading engine <on>\n"
    "-cuda			Run sequential cuda engine <on>\n"
    "-mpi			Run sequential mpi engine <on>\n"
    "-help			Print help message <on>\n"
    "-dataset_csv	        Set dataset.csv file path. If not specify dataset matrix will be generate\n"
    "-query_csv		Set query.csv file path. If not specify query matrix will be generate\n";

    std::cout<<msg<<std::endl;
}

int main(int argc, char **argv) {
    dce::log4dce *logger = dce::log4dce::get_root();
    dce::csv_writer writer;
    dce::fmatrix query, dataset, hamming_out, l1_out, l2_out;

    try {
        dce::settings settings;
        settings.parse_args(argc, argv);

        if(settings.get_command_value(dce::settings::commands::help) == dce::settings::values::on) {
            print_help();
            exit(0);
        }

        if (settings.get_command_value(dce::settings::commands::query_csv) == dce::settings::values::empty &&
            settings.get_command_value(dce::settings::commands::dataset_csv) == dce::settings::values::empty) {

            dce::json_reader reader;
            reader.read("cfg/input_generator_config.json");

            dce::input_generator generator;
            generator.set_count(reader.get_value("vectors_count"));
            generator.set_lenght(reader.get_value("vector_lenght"));
            generator.set_start(reader.get_value("start"));
            generator.set_end(reader.get_value("end"));

            query = generator.generate();
            writer.write("./csv_files/input/query.csv", query);
            dataset = generator.generate();
            writer.write("./csv_files/input/dataset.csv", query);
        } else {
            dce::csv_reader reader;
            query = reader.read(settings.get_command_value(dce::settings::commands::query_csv));
            dataset = reader.read(settings.get_command_value(dce::settings::commands::dataset_csv));
        }

        dce::engine engine;
        if(settings.get_command_value(dce::settings::commands::seq) == dce::settings::values::on) {
            dce::timing::tic();
            hamming_out = engine.run(query, dataset, dce::metrics::hamming::sequential_distance<float, dce::fvector::const_iterator>);
            logger->info("Sequential hamming distance running time: " + std::to_string(dce::timing::toc()));

            dce::timing::tic();
            l1_out = engine.run(query, dataset, dce::metrics::l1::sequential_distance<float, dce::fvector::const_iterator>);
            logger->info("Sequential l1 distance running time: " + std::to_string(dce::timing::toc()));

            dce::timing::tic();
            l2_out = engine.run(query, dataset, dce::metrics::l2::sequential_distance<float, dce::fvector::const_iterator>);
            logger->info("Sequential l2 distance running time: " + std::to_string(dce::timing::toc()));

        } else if(settings.get_command_value(dce::settings::commands::mpi) == dce::settings::values::on) {
//            hamming_out = engine.run(query, dataset, dce::metrics::hamming::mpi_distance<float, dce::fvector::const_iterator>);
//            l1_out = engine.run(query, dataset, dce::metrics::l1::mpi_distance<float, dce::fvector::const_iterator>);
//            l2_out = engine.run(query, dataset, dce::metrics::l2::mpi_distance<float, dce::fvector::const_iterator>);

        } else if(settings.get_command_value(dce::settings::commands::multi) == dce::settings::values::on) {
            hamming_out = engine.run(query, dataset, dce::metrics::hamming::parallel_distance<float, dce::fvector::const_iterator>);
            l1_out = engine.run(query, dataset, dce::metrics::l1::parallel_distance<float, dce::fvector::const_iterator>);
            l2_out = engine.run(query, dataset, dce::metrics::l2::parallel_distance<float, dce::fvector::const_iterator>);

        } else if(settings.get_command_value(dce::settings::commands::cuda) == dce::settings::values::on) {
//            hamming_out = engine.run(query, dataset, dce::metrics::cuda::hamming::cuda_distance<float, dce::fvector::const_iterator>);
//            l1_out = engine.run(query, dataset, dce::metrics::l1::cuda_distance<float, dce::fvector::const_iterator>);
//            l2_out = engine.run(query, dataset, dce::metrics::l2::cuda_distance<float, dce::fvector::const_iterator>);

        } else {
            exit(-1);
        }

        if(settings.get_command_value(dce::settings::commands::print) == dce::settings::values::file) {
            writer.write("./csv_files/output/1hamming_sequential_distance.csv", hamming_out);
            writer.write("./csv_files/output/1l1_sequential_distance.csv", l1_out);
            writer.write("./csv_files/output/1l2_sequential_distance.csv", l2_out);
        } else {
            print_into_terminal(hamming_out);
            print_into_terminal(l1_out);
            print_into_terminal(l2_out);
        }

    } catch (std::runtime_error &er) {
        std::cout << "[EXCEPTION]: " << er.what() << std::endl;
        logger->error(er.what());
    }

    return 0;
}
