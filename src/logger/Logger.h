#pragma once

#include <string>
#include <iostream>
#include <ctime>
#include <cstdarg>

class Color {
    public:
        static std::string RED;
        static std::string GREEN;
        static std::string YELLOW;
        static std::string BLUE;
        static std::string MAGENTA;
        static std::string CYAN;
        static std::string WHITE;
        static std::string RESET;
};

class Logger {
    public:
        static void debug(std::string format, ...);
        static void info(std::string format, ...);
        static void warning(std::string format, ...);
        static void error(std::string format, ...);
};
