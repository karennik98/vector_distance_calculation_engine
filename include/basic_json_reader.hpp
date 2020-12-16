#pragma once

#include <unordered_map>
#include <fstream>

namespace dce {
        class json_reader {
        public:
            json_reader() = default;
            ~json_reader() = default;

        public:
            void read(const std::string& file);
        public:
            float get_value(const std::string& key) const noexcept;

        private:
            struct jsymbols {
                inline static const std::string start_bracket = "{";
                inline static const std::string end_bracket = "}";
                inline static const std::string ending = ":";
                inline static const std::string comma = ",";
            };
        private:
            void open(const std::string& file);
            void remove_whitespace(std::string& line) const noexcept;
            std::string read_key(std::string line) const noexcept;
            float read_value(std::string line) const noexcept;
        private:
            std::ifstream file_;
            std::unordered_map<std::string, float> jcontent_;
        };
}