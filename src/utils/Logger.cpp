#include "utils/Logger.h"
#include <iostream>
#include <cstdarg>

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

void Logger::debug(std::string format, ...) {
	if (format.empty()) {
		std::cout << std::endl;
		return;
	}

	va_list args;
	va_start(args, format);

	format = prepare(format);

	std::cout << Color::GREEN << "[DEBUG]" << " ";
	std::vprintf(format.c_str(), args);
	std::cout << Color::RESET << std::endl;

	va_end(args);
}

void Logger::info(std::string format ...) {
	if (format.empty()) {
		std::cout << std::endl;
		return;
	}

	va_list args;
	va_start(args, format);

	format = prepare(format);

	std::cout << Color::BRIGHT_WHITE << "[INFO]" << " ";
	std::vprintf(format.c_str(), args);
	std::cout << Color::RESET << std::endl;

	va_end(args);
}

void Logger::warning(std::string format, ...) {
	if (format.empty()) {
		std::cout << std::endl;
		return;
	}

	va_list args;
	va_start(args, format);

	format = prepare(format);

	std::cout << Color::BRIGHT_YELLOW << "[INFO]" << " ";
	std::vprintf(format.c_str(), args);
	std::cout << Color::RESET << std::endl;

	va_end(args);
}

void Logger::error(std::string format, ...) {
	if (format.empty()) {
		std::cout << std::endl;
		return;
	}

	va_list args;
	va_start(args, format);

	format = prepare(format);

	std::cout << Color::BRIGHT_RED << "[ERROR]" << " ";
	std::vprintf(format.c_str(), args);
	std::cout << Color::RESET << std::endl;

	va_end(args);
}
