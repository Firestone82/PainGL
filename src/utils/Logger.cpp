#include "utils/Logger.h"
#include <iostream>
#include <cstdarg>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <vector>

std::string currentTimestamp() {
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
	return ss.str();
}

std::string prepare(std::string format) {
	if (format.size() > 2 && (format[0] == '\\' && format[1] == 'n')) {
		std::cout << std::endl;
		format.erase(0, 2);
	}

	if (format[0] == '\n') {
		std::cout << std::endl;
		format.erase(0, 1);
	}

	return format;
}

void log(const std::string& level, const std::string& levelColor, const std::string& logColor, std::string format, va_list args) {
	if (format.empty()) {
		std::cout << std::endl;
		return;
	}

	std::istringstream stream(prepare(format));
	std::string line;

	while (std::getline(stream, line)) {
		std::string levelType = level;
		levelType.resize(5, ' ');

		std::cout << Color::WHITE << "[" << Color::GRAY << currentTimestamp() << Color::WHITE << "] ";
		std::cout << levelColor << levelType << Color::RESET << " | " << logColor;
		std::vprintf(line.c_str(), args);
		std::cout << Color::RESET << std::endl;
	}
}

void Logger::debug(std::string format, ...) {
	va_list args;
	va_start(args, format);
	log("DEBUG", Color::BOLD_GREEN, Color::GREEN, format, args);
	va_end(args);
}

void Logger::info(std::string format, ...) {
	va_list args;
	va_start(args, format);
	log("INFO", Color::BOLD_CYAN,Color::CYAN, format, args);
	va_end(args);
}

void Logger::warning(std::string format, ...) {
	va_list args;
	va_start(args, format);
	log("WARN", Color::BOLD_YELLOW, Color::YELLOW, format, args);
	va_end(args);
}

void Logger::error(std::string format, ...) {
	va_list args;
	va_start(args, format);
	log("ERROR", Color::BOLD_RED, Color::RED, format, args);
	va_end(args);
}