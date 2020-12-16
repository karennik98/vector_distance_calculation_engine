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

    class log4dce {
    public:
        log4dce(const log4dce&) = delete;
        log4dce(log4dce&&) = delete;

    public:
        static log4dce *get_root();

    public:
        void info(const std::string &msg);
        void warn(const std::string &msg);
        void error(const std::string &msg);

    protected:
        log4dce() = default;
        ~log4dce() = default;

    private:
        static log4dce* root_;
    private:
        std::string file_path_;
        std::ofstream file_writer_;
    };
}
