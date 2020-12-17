#include "log4dce.hpp"
#include "timing.hpp"

namespace dce {
    log4dce *log4dce::root_ = nullptr;
    std::mutex mtx;

    log4dce *log4dce::get_root() {
        {
            std::lock_guard<std::mutex> lc(mtx);
            if (root_ == nullptr) {
                root_ = new log4dce;
            }
        }
        return root_;
    }

    void log4dce::info(const std::string &msg) {
        file_writer_.open("./log.txt", std::ios::out | std::ios::app);
        if (file_writer_.is_open()) {
            file_writer_ << messages::INFO << "[" << dce::timing::now() << "] " << msg << messages::ENDLINE;
            file_writer_.close();
            return;
        }
        std::runtime_error("log4dce file did not open");
    }

    void log4dce::warn(const std::string &msg) {
        file_writer_.open("./log.txt", std::ios::out | std::ios::app);
        if (file_writer_.is_open()) {
            file_writer_ << messages::WARN << "[" << dce::timing::now() << "] " << msg << messages::ENDLINE;
            file_writer_.close();
            return;
        }
        std::runtime_error("log4dce file did not open");
    }

    void log4dce::error(const std::string &msg) {
        file_writer_.open("./log.txt", std::ios::out | std::ios::app);
        if (file_writer_.is_open()) {
            file_writer_ << messages::ERROR << "[" << dce::timing::now() << "] " << msg << messages::ENDLINE;
            file_writer_.close();
            return;
        }
        std::runtime_error("log4dce file did not open");
    }
}