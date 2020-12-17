#include "timing.hpp"

#include <chrono>
#include <vector>

namespace dce
{
    namespace timing
    {
        namespace
        {
            using time = std::chrono::high_resolution_clock;
            using ms = std::chrono::milliseconds;
            using fsec = std::chrono::duration<float>;
            static std::vector<decltype(time::now())> tictoc_stack;
        }

        void tic() noexcept
        {
            tictoc_stack.push_back(time::now());
        }

        std::string now() noexcept
        {
            std::time_t t = std::time(0);
            std::tm *now = std::localtime(&t);
            std::string data_time;
            data_time.append(std::to_string(now->tm_year + 1900) + ':');
            data_time.append(std::to_string(now->tm_mon + 1) + ':');
            data_time.append(std::to_string(now->tm_mday));
            return data_time;
        }

        float toc() noexcept
        {
            fsec fs = time::now() - tictoc_stack.back();
            auto i = tictoc_stack.begin();
            std::string diff;
            while (i != tictoc_stack.end()) {
                diff += "  ";
                ++i;
            }
            auto proc_time = fs.count();
            tictoc_stack.pop_back();
            return proc_time;
        }
    }
}