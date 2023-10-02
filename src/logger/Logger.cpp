#include "Logger.h"

std::string Color::RED = "\033[31m";
std::string Color::GREEN = "\033[32m";
std::string Color::YELLOW = "\033[33m";
std::string Color::BLUE = "\033[34m";
std::string Color::MAGENTA = "\033[35m";
std::string Color::CYAN = "\033[36m";
std::string Color::WHITE = "\033[37m";
std::string Color::RESET = "\033[0m";

void Logger::debug(std::string format, ...) {
    va_list args;
    va_start(args, format);

    std::cout << Color::GREEN << "[DEBUG]" << " ";
    std::vprintf(format.c_str(), args);
    std::cout << Color::RESET << std::endl;

    va_end(args);
}

void Logger::info(std::string format ...) {
    va_list args;
    va_start(args, format);

    std::cout << Color::WHITE << "[INFO]" << " ";
    std::vprintf(format.c_str(), args);
    std::cout << Color::RESET << std::endl;

    va_end(args);
}

void Logger::warning(std::string format, ...) {
    va_list args;
    va_start(args, format);

    std::cout << Color::YELLOW << "[INFO]" << " ";
    std::vprintf(format.c_str(), args);
    std::cout << Color::RESET << std::endl;

    va_end(args);
}

void Logger::error(std::string format, ...) {
    va_list args;
    va_start(args, format);

    std::cout << Color::RED << "[ERROR]" << " ";
    std::vprintf(format.c_str(), args);
    std::cout << Color::RESET << std::endl;

    va_end(args);
}