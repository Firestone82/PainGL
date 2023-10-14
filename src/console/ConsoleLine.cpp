#include "console/ConsoleLine.h"

ConsoleLine::ConsoleLine(const std::string& text, bool command) : command(command), text(text) {}

bool ConsoleLine::isCommand() const {
	return command;
}

std::string ConsoleLine::getText() const {
	return text;
}

time_t ConsoleLine::getTimestamp() const {
	return timestamp;
}