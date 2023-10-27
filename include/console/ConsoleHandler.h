#pragma once

#include "3rdparty/imgui/imgui.h"
#include "console/ConsoleCommand.h"
#include "console/ConsoleLine.h"

#include <string>
#include <vector>

class ConsoleHandler {
	private:
		std::string title;

		std::vector<ConsoleCommand*> commands;
		std::vector<ConsoleLine*> log;

		std::vector<std::string> history;
		std::vector<std::string> suggestions;
		char inputBuffer[256]{};
		int historyPos = -1;

		bool enabled = false;
		void fillCommands();

	public:
		explicit ConsoleHandler(std::string title);
		/* - */ ~ConsoleHandler();

		void addLog(bool command, const char* fmt, ...);
		void clearLog();

		void setEnabled(bool enabled);
		bool isEnabled() const;

		void render();

		static int textEditCallbackStub(ImGuiInputTextCallbackData* data);
		int textEditCallback(ImGuiInputTextCallbackData* data);

		void executeCommand(const char* command_line);
		void addCommand(ConsoleCommand* command);
		std::vector<ConsoleCommand*> getCommands() const;
};