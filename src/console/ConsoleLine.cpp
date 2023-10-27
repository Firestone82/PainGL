#include "console/ConsoleLine.h"

#include <utility>

ConsoleLine::ConsoleLine(std::string text, bool command) : command(command), text(std::move(text)) {
	/* Empty */
}

bool ConsoleLine::isCommand() const {
	return command;
}

std::string ConsoleLine::getText() const {
	return text;
}

time_t ConsoleLine::getTimestamp() const {
	return timestamp;
}