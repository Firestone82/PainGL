#pragma once

#include <string>
#include <chrono>

static const auto timeBegin = std::chrono::steady_clock::now();

class ConsoleLine {
	private:
		unsigned int timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::steady_clock::now() - timeBegin
		).count();

		bool command = false;
		std::string text;

	public:
		ConsoleLine(std::string text, bool command);
		~ConsoleLine() = default;

		bool isCommand() const;
		std::string getText() const;
		time_t getTimestamp() const;
};
