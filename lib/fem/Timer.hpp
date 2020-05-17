#pragma once

#include <chrono>
#include <iostream>

class Timer {
public:
    explicit Timer(std::string name)
        : m_name(std::move(name))
        , m_start(std::chrono::steady_clock::now()) {
    }

    ~Timer() {
        auto end = std::chrono::steady_clock::now();
        std::cout << m_name << ": " << std::chrono::duration_cast<std::chrono::microseconds>(end - m_start).count() / (1000.0f * 1000.0f)
                  << "s\n\b";
    }

private:
    std::string m_name;
    std::chrono::steady_clock::time_point m_start;
};