#pragma once

#include <string>

class Color {
	public:
		// Standard colors
		static inline std::string BLACK = "\033[0;30m";
		static inline std::string RED = "\033[0;31m";
		static inline std::string GREEN = "\033[0;32m";
		static inline std::string YELLOW = "\033[0;33m";
		static inline std::string BLUE = "\033[0;34m";
		static inline std::string MAGENTA = "\033[0;35m";
		static inline std::string CYAN = "\033[0;36m";
		static inline std::string GRAY = "\033[0;37m";
		static inline std::string WHITE = "\033[0;38m";

		// Bright colors
		static inline std::string BOLD_BLACK = "\033[1;30m";
		static inline std::string BOLD_RED = "\033[1;31m";
		static inline std::string BOLD_GREEN = "\033[1;32m";
		static inline std::string BOLD_YELLOW = "\033[1;33m";
		static inline std::string BOLD_BLUE = "\033[1;34m";
		static inline std::string BOLD_MAGENTA = "\033[1;35m";
		static inline std::string BOLD_CYAN = "\033[1;36m";
		static inline std::string BOLD_GRAY = "\033[1;37m";
		static inline std::string BOLD_WHITE = "\033[1;38m";

		// Reset color
		static inline std::string RESET = "\033[0m";
};

class Logger {
	public:
		/**
		 * @brief Prepares the format string for printing.
		 * @param format The format string.
		 * @param ... The arguments.
		 */
		static void debug(std::string format, ...);

		/**
		 * @brief Prints an info message to the console.
		 * @param format The format string.
		 * @param ... The arguments.
		 */
		static void info(std::string format, ...);

		/**
		 * @brief Prints a warning message to the console.
		 * @param format The format string.
		 * @param ... The arguments.
		 */
		static void warning(std::string format, ...);

		/**
		 * @brief Prints an error message to the console.
		 * @param format The format string.
		 * @param ... The arguments.
		 */
		static void error(std::string format, ...);
};