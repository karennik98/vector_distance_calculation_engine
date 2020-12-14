#pragma once

#include <string>
#include <mutex>
#include <fstream>

namespace dce {
    struct messages {
        inline static const std::string INFO ="[INFO]: ";
        inline static const std::string WARN ="[WARN]: ";
        inline static const std::string ERROR="[ERROR]: ";
        inline static const std::string ENDLINE="\n";
    };

    class logger {
    public:
        logger(const logger&) = delete;
        logger(logger&&) = delete;

    public:
        static logger *get_root();

    public:
        void info(const std::string &msg);
        void warn(const std::string &msg);
        void error(const std::string &msg);

    protected:
        logger() = default;
        ~logger() = default;

    private:
        static logger* root_;
    private:
        std::string file_path_;
        std::ofstream file_writer_;
    };
}
