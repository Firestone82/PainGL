#include "console/ConsoleCommand.h"

#include <utility>

ConsoleCommand::ConsoleCommand(std::string name) : name(std::move(name)) {
	/* Empty */
}

std::string ConsoleCommand::getName() const {
	return this->name;
}

std::string ConsoleCommand::getDescription() const {
	return this->description;
}

std::string ConsoleCommand::getUsage() const {
	return this->usage;
}

int ConsoleCommand::getMinArgs() const {
	return this->minArgs;
}

int ConsoleCommand::getMaxArgs() const {
	return this->maxArgs;
}

void ConsoleCommand::execute(const std::vector<std::string> &args) {
	this->callback(args);
}

// -- Builder --

ConsoleCommand::Builder::Builder(const std::string &name) {
	this->consoleCommand = new ConsoleCommand(name);
}

ConsoleCommand::Builder* ConsoleCommand::Builder::setDescription(const std::string &description) {
	this->consoleCommand->description = description;
	return this;
}

ConsoleCommand::Builder* ConsoleCommand::Builder::setUsage(const std::string &usage) {
	this->consoleCommand->usage = usage;
	return this;
}

ConsoleCommand::Builder* ConsoleCommand::Builder::setMinArgs(int minArgs) {
	this->consoleCommand->minArgs = minArgs;
	return this;
}

ConsoleCommand::Builder* ConsoleCommand::Builder::setMaxArgs(int maxArgs) {
	this->consoleCommand->maxArgs = maxArgs;
	return this;
}

ConsoleCommand::Builder* ConsoleCommand::Builder::setCallback(const std::function<void(const std::vector<std::string>&)> &callback) {
	this->consoleCommand->callback = callback;
	return this;
}

ConsoleCommand* ConsoleCommand::Builder::build() {
	return this->consoleCommand;
}

ConsoleCommand::Builder* ConsoleCommand::createCommand(const std::string &name) {
	return new Builder(name);
}