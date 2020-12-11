#include "csv_reader.hpp"

#include <sstream>
#include <iostream>


namespace dce {

    fmatrix csv_reader::read(const std::string &file) {
        fmatrix data;
        std::string line, colname;
        int val;

        open(file);

        while(std::getline(file_, line))
        {
            std::stringstream ss(line);
            int column_idx = 0;
            fvector temp_vec;

            while(ss >> val){
                temp_vec.push_back(val);
                if(ss.peek() == ',') ss.ignore();
                column_idx++;
            }
            data.push_back(temp_vec);
        }

        file_.close();
        return data;
    }

    void csv_reader::open(const std::string& file) {
        file_.open(file);
        if(!file_.is_open()) {
            throw std::runtime_error("Could not open file");
        }
    }
}