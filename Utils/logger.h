#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <string>

inline void log_event(int tick, const std::string& level, const std::string& msg) {
    std::cout << "[t=" << tick << "][" << level << "] " << msg << "\n";
}
#endif