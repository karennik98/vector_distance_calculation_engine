#include "logger.hpp"

namespace dce {
    logger *logger::root_ = nullptr;
    std::mutex mtx;

    logger *logger::get_root() {
        {
            std::lock_guard<std::mutex> lc(mtx);
            if (root_ == nullptr) {
                root_ = new logger;
            }
        }
        return root_;
    }

    void logger::info(const std::string &msg) {
        file_writer_.open("./log.txt", std::ios::out | std::ios::app);
        if (file_writer_.is_open()) {
            file_writer_ << messages::INFO << msg << messages::ENDLINE;
            file_writer_.close();
            return;
        }
        std::runtime_error("Logger file did not open");
    }

    void logger::warn(const std::string &msg) {
        file_writer_.open("./log.txt", std::ios::out | std::ios::app);
        if (file_writer_.is_open()) {
            file_writer_ << messages::WARN << msg << messages::ENDLINE;
            file_writer_.close();
            return;
        }
        std::runtime_error("Logger file did not open");
    }

    void logger::error(const std::string &msg) {
        file_writer_.open("./log.txt", std::ios::out | std::ios::app);
        if (file_writer_.is_open()) {
            file_writer_ << messages::ERROR << msg << messages::ENDLINE;
            file_writer_.close();
            return;
        }
        std::runtime_error("Logger file did not open");
    }
}