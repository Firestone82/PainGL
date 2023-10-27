#pragma once

#include <string>

class Color {
	public:
		// Text colors
		static inline std::string RED = "\033[0;31m";
		static inline std::string GREEN = "\033[32m";
		static inline std::string YELLOW = "\033[33m";
		static inline std::string BLUE = "\033[34m";
		static inline std::string MAGENTA = "\033[35m";
		static inline std::string CYAN = "\033[36m";
		static inline std::string WHITE = "\033[97m";
		static inline std::string DARK_GRAY = "\033[90m";
		static inline std::string GRAY = "\033[37m";
		static inline std::string BRIGHT_RED = "\033[91m";
		static inline std::string BRIGHT_GREEN = "\033[92m";
		static inline std::string BRIGHT_YELLOW = "\033[93m";
		static inline std::string BRIGHT_BLUE = "\033[94m";
		static inline std::string BRIGHT_MAGENTA = "\033[95m";
		static inline std::string BRIGHT_CYAN = "\033[96m";
		static inline std::string BRIGHT_WHITE = "\033[97m";

		// Background colors
		static inline std::string BACKGROUND_RED = "\033[41m";
		static inline std::string BACKGROUND_GREEN = "\033[42m";
		static inline std::string BACKGROUND_YELLOW = "\033[43m";
		static inline std::string BACKGROUND_BLUE = "\033[44m";
		static inline std::string BACKGROUND_MAGENTA = "\033[45m";
		static inline std::string BACKGROUND_CYAN = "\033[46m";
		static inline std::string BACKGROUND_WHITE = "\033[107m";
		static inline std::string BACKGROUND_DARK_GRAY = "\033[100m";
		static inline std::string BACKGROUND_GRAY = "\033[47m";
		static inline std::string BACKGROUND_BRIGHT_RED = "\033[101m";
		static inline std::string BACKGROUND_BRIGHT_GREEN = "\033[102m";
		static inline std::string BACKGROUND_BRIGHT_YELLOW = "\033[103m";
		static inline std::string BACKGROUND_BRIGHT_BLUE = "\033[104m";
		static inline std::string BACKGROUND_BRIGHT_MAGENTA = "\033[105m";
		static inline std::string BACKGROUND_BRIGHT_CYAN = "\033[106m";
		static inline std::string BACKGROUND_BRIGHT_WHITE = "\033[107m";

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