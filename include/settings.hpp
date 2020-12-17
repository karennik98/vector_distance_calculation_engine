#pragma once

#include <vector>
#include <string>
#include <unordered_map>

namespace dce {
    class settings {
    public:
        settings();
        ~settings() = default;

    public:
        std::string get_command_value(const std::string& key) const noexcept;

    public:
        void parse_args(int argc, char *argv[]);

    private:
        void init_default_commands() noexcept;

    private:
        bool is_correct_value(const std::string& value) const;
        bool is_correct_order() const;
        bool has_ending (std::string const &str) const noexcept;

    public:
        struct commands {
            inline static const std::string query_csv ="-query_csv";
            inline static const std::string dataset_csv ="-dataset_csv";
            inline static const std::string multi="-multi";
            inline static const std::string cuda="-cuda";
            inline static const std::string mpi="-mpi";
            inline static const std::string seq="-seq";
            inline static const std::string help="-help";
            inline static const std::string print="-print";
        };

        struct values {
            inline static const std::string on = "on";
            inline static const std::string off = "off";
            inline static const std::string csv = "csv";
            inline static const std::string empty = "";
            inline static const std::string invalid = "invalid";
            inline static const std::string terminal = "terminal";
            inline static const std::string file = "file";
        };
    private:
        std::unordered_map<std::string, std::string> args_;
    };
}

// ./main -query_csv lala.csv -dataset_csv lala.csv -multi on || -cuda on || -mpi on || -help