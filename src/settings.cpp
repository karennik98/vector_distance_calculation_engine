#include "settings.hpp"

namespace dce {
    settings::settings() {
        init_default_commands();
    }

    void settings::init_default_commands() noexcept {
        args_ = {
                {commands::query_csv,   values::empty},
                {commands::dataset_csv, values::empty},
                {commands::multi,       values::off},
                {commands::seq,         values::off},
                {commands::mpi,         values::off},
                {commands::cuda,        values::off},
                {commands::help,        values::off}
        };
    }

    std::string settings::get_command_value(const std::string& key) const noexcept {
        if(auto value = args_.find(key); value != args_.end()) {
           return value->second;
        }
        return values::invalid;
    }

    void settings::parse_args(int argc, char **argv) {
        for (int i = 1; i < argc; ++i) {
            if (argv[i] == commands::help) {
                std::string value = argv[++i];
                args_[commands::help] = is_correct_value(value) ? value : values::invalid;
            } else if (argv[i] == commands::cuda) {
                std::string value = argv[++i];
                args_[commands::cuda] = is_correct_value(value) ? value : values::invalid;
            } else if (argv[i] == commands::mpi) {
                std::string value = argv[++i];
                args_[commands::mpi] = is_correct_value(value) ? value : values::invalid;
            } else if (argv[i] == commands::seq) {
                std::string value = argv[++i];
                args_[commands::seq] = is_correct_value(value) ? value : values::invalid;
            } else if (argv[i] == commands::dataset_csv) {
                std::string value = argv[++i];
                args_[commands::dataset_csv] = is_correct_value(value) ? value : values::empty;
            } else if (argv[i] == commands::query_csv) {
                std::string value = argv[++i];
                args_[commands::query_csv] = is_correct_value(value) ? value : values::empty;
            } else if (argv[i] == commands::multi) {
                std::string value = argv[++i];
                args_[commands::multi] = is_correct_value(value) ? value : values::invalid;
            } else {
                throw std::runtime_error("Ivalid command ");
            }
        }

        is_correct_order();
    }

    bool settings::is_correct_value(const std::string &value) const {
        return value == values::on || value == values::off || has_ending(value);
    }

    bool settings::is_correct_order() const {
        uint8_t count = 0;
        if(args_.at(commands::multi) == values::on) {
            count++;
        }
        if(args_.at(commands::cuda) == values::on) {
            count++;
        }
        if(args_.at(commands::seq) == values::on) {
            count++;
        }
        if(args_.at(commands::mpi) == values::on) {
            count++;
        }

        if(count == 0 && args_.at(commands::help) != values::on) {
            throw std::runtime_error("No engine type specify");
        } else if(count > 1) {
            throw std::runtime_error("Multiple engines are specify");
        }

        return true;
    }

    bool settings::has_ending(std::string const &str) const noexcept {
        if (str.length() >= values::csv.length()) {
            return (0 == str.compare(str.length() - values::csv.length(), values::csv.length(), values::csv));
        }
        return false;
    }
}