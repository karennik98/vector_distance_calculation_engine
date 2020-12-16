#include "basic_json_reader.hpp"

#include <sstream>
#include <string>

namespace dce {

    void json_reader::read(const std::string &file) {
        std::string line, colname;
        int val;

        open(file);

        while(std::getline(file_, line))
        {
            if(line == jsymbols::start_bracket || line == jsymbols::end_bracket) {
                continue;
            }

            remove_whitespace(line);

            std::string key = read_key(line);
            float value =  read_value(line);

            jcontent_[key] = value;
        }

        file_.close();
    }

    float json_reader::get_value(const std::string &key) const noexcept {
        if(auto value = jcontent_.find(key); value != jcontent_.end()) {
            return value->second;
        }
        throw std::runtime_error("Invalid json key");
    }

    void json_reader::open(const std::string& file) {
        file_.open(file);
        if(!file_.is_open()) {
            throw std::runtime_error("Could not open file");
        }
    }

    void json_reader::remove_whitespace(std::string& line) const noexcept {
        while (line.at(0) == ' ') {
            line.erase(line.begin());
        }
    }

    std::string json_reader::read_key(std::string line) const noexcept {
        if(size_t start_pos = line.find('"'); start_pos != std::string::npos) {
            line.erase(start_pos, 1);
            if(size_t end_pos = line.find('"'); end_pos != std::string::npos) {
                return line.substr(start_pos, end_pos);
            }
        }
        throw std::runtime_error("Invalid json key");
    }

    float json_reader::read_value(std::string line) const noexcept {
        if(size_t start_pos = line.find(':'); start_pos != std::string::npos) {
            line = line.substr(start_pos + 1, line.size());
            while (line.at(0) == ' ') {
                line.erase(line.begin());
            }
            start_pos = 0;
            if(size_t end_pos = line.find(','); end_pos != std::string::npos) {
                return std::stof(line.substr(start_pos, end_pos));
            } else {
                return std::stof(line.substr(start_pos, line.size()));
            }
        }
        throw std::runtime_error("Invalid json value");
    }

}