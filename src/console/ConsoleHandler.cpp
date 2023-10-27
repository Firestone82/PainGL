#include "Engine.h"
#include "console/ConsoleHandler.h"
#include "event/type/KeyBoardEvents.h"
#include "utils/StringUtils.h"

#include <utility>

ConsoleHandler::ConsoleHandler(std::string title) : title(std::move(title)) {
	memset(this->inputBuffer, 0, sizeof(this->inputBuffer));
	this->clearLog();

	// Listener for opening/closing console on press of ` or ESC
	Engine::getInstance()->getEventHandler()->addListener(new Listener<KeyPressEvent>([=](KeyPressEvent* event) {
		if ((event->getKey() == GLFW_KEY_GRAVE_ACCENT || (event->getKey() == GLFW_KEY_ESCAPE && isEnabled())) && event->getAction() == GLFW_PRESS) {
			this->setEnabled(!this->isEnabled());
		}
	}));

	// Fill commands into console
	fillCommands();
}

ConsoleHandler::~ConsoleHandler() {
	this->clearLog();
}

void ConsoleHandler::addLog(bool command, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);

	char buf[1024];
	vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
	buf[IM_ARRAYSIZE(buf) - 1] = 0;
	this->log.emplace_back(new ConsoleLine(strdup(buf), command));

	va_end(args);
}

void ConsoleHandler::clearLog() {
	for (const auto& line : this->log) {
		delete line;
	}

	this->log.clear();
	this->historyPos = -1;
	memset(this->inputBuffer, 0, sizeof(this->inputBuffer));
}

static bool reclaim_focus = false;
void ConsoleHandler::setEnabled(bool enabled) {
	this->enabled = enabled;

	Engine* engine = Engine::getInstance();
	static bool lastState = false;

	if (enabled) {
		lastState = engine->getWindowHandler()->isCursorEnabled();
		engine->getWindowHandler()->setCursorEnabled(true);

		ImGui::SetWindowFocus(title.c_str());
		reclaim_focus = true;
	} else {
		engine->getWindowHandler()->setCursorEnabled(lastState);
	}
}

bool ConsoleHandler::isEnabled() const {
	return this->enabled;
}

void ConsoleHandler::render() {
	int width = Engine::getInstance()->getWindowHandler()->getWidth();

	ImGui::SetNextWindowSize(ImVec2(500, 600), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos({float(width - 500 - 15), 15.0f}, ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(this->title.c_str(), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings)) {
		ImGui::End();
		return;
	}

	const float footerReserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing() + 3;
	if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footerReserve), false, ImGuiWindowFlags_HorizontalScrollbar)) {
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1));

		// Display lines in console
		for (const auto& item : log) {
			bool has_color = false;
			ImVec4 color;

			// Set type color
			if (item->getText().find("[warning]") != std::string::npos) {
				color = ImVec4(1.0f, 0.4f, 0.0f, 1.0f);
				has_color = true;
			} else if (item->getText().find("[error]") != std::string::npos) {
				color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f);
				has_color = true;
			} else if (item->getText().compare(0, 2, "> ") == 0) {
				color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f);
				has_color = true;
			} else if (item->getText().compare(0, 2, "# ") == 0) {
				color = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
				has_color = true;
			}

			if (has_color) ImGui::PushStyleColor(ImGuiCol_Text, color);
			ImGui::TextUnformatted(item->getText().c_str());
			if (has_color) ImGui::PopStyleColor();

			// Add timestamp
			if (item->isCommand()) {
				static const float timestamp_width = ImGui::CalcTextSize("00:00:00 ").x;
				ImGui::SameLine(ImGui::GetColumnWidth(-1) - timestamp_width);

				ImGui::PushStyleColor(ImGuiCol_Text, {0.3f, 0.3f, 0.3f, 1.0f});
				ImGui::Text("%02d:%02d:%02d ", ((item->getTimestamp() / 1000 / 3600) % 24), ((item->getTimestamp() / 1000 / 60) % 60), ((item->getTimestamp() / 1000) % 60));
				ImGui::PopStyleColor();
			}
		}

		// Scroll to bottom
		if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
			ImGui::SetScrollHereY(1.0f);
		}

		ImGui::PopStyleVar();
		ImGui::EndChild();
	}

	// Separator
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 7)); // Tighten spacing
	ImGui::Separator();
	ImGui::PopStyleVar();

	// Command-line
	ImGui::PushItemWidth(-ImGui::GetStyle().ItemSpacing.x * 13);
	ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll | ImGuiInputTextFlags_CallbackEdit | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
	ImGui::InputText("##Input", this->inputBuffer, IM_ARRAYSIZE(this->inputBuffer), input_text_flags, &textEditCallbackStub, (void*) this);

	// Suggestions
	if (!this->suggestions.empty()) {
		ImGui::SetNextWindowPos({ImGui::GetItemRectMin().x, ImGui::GetItemRectMax().y});

		ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoMouseInputs;
		if (ImGui::Begin("TooltipCommands", nullptr, flags)) {
			for (const auto& suggestion : this->suggestions) {
				ImGui::Text("%s", suggestion.c_str());
			}
		}

		ImGui::End();
	}

	// Autofocus on window apparition
	ImGui::SetItemDefaultFocus();
	if (reclaim_focus) {
		ImGui::SetKeyboardFocusHere(-1);
		reclaim_focus = false;
	}

	// Execute command button
	ImGui::SameLine();
	if (ImGui::Button("Send") || ImGui::IsKeyPressed(ImGuiKey_Enter, false) || ImGui::IsKeyPressed(ImGuiKey_KeyPadEnter, false)) {
		char* s = this->inputBuffer;
		while (*s == ' ') s++;

		executeCommand(s);
		suggestions.clear();

		memset(this->inputBuffer, 0, sizeof(this->inputBuffer));
		reclaim_focus = true;
	}

	// Clear console button
	ImGui::SameLine();
	if (ImGui::Button("Clear")) {
		clearLog();
	}

	ImGui::End();
}

void ConsoleHandler::executeCommand(const char *command_line) {
	// Add to log
	addLog(true,"> %s\n", command_line);

	// Add to history
	this->historyPos = -1;
	this->history.erase(std::remove(this->history.begin(), this->history.end(), command_line), this->history.end());
	this->history.emplace_back(strdup(command_line));

	// Parse arguments from command line
	std::vector<std::string> args = StringUtils::split(command_line, " ");
	args.erase(std::remove_if(args.begin(), args.end(), [](const std::string& arg) {
		return arg.empty();
	}), args.end());
	int argc = static_cast<int>(args.size()) - 1;

	// Process command
	for (const auto& command : this->commands) {
		if (strcasecmp(command->getName().c_str(), args[0].c_str()) == 0) {
			if (argc < command->getMinArgs() || argc > command->getMaxArgs()) {
				addLog(false,"\n[error] Wrong usage! Use: %s ", command->getUsage().c_str());
				addLog(false,"");
				return;
			}

			command->execute(args);
			addLog(false,"");

			return;
		}
	}

	addLog(false,"\n Unknown command: '%s'", command_line);
	addLog(false,"");
}

void ConsoleHandler::addCommand(ConsoleCommand *command) {
	this->commands.emplace_back(command);
}

std::vector<ConsoleCommand*> ConsoleHandler::getCommands() const {
	return this->commands;
}

int ConsoleHandler::textEditCallbackStub(ImGuiInputTextCallbackData *data) {
	auto* console = (ConsoleHandler*) data->UserData;
	return console->textEditCallback(data);
}

int ConsoleHandler::textEditCallback(ImGuiInputTextCallbackData* data) {
	const char* line = data->Buf;

	// Remove trailing and leading spaces
	while (*line == ' ') line++;
	char* line_end = (char*) line + strlen(line);
	while (line_end > line && line_end[-1] == ' ') line_end--;

	std::vector<std::string> args = StringUtils::split(line, " ");
	if (args.empty()) return 1;

	switch (data->EventFlag) {
		case ImGuiInputTextFlags_CallbackEdit: {
			this->suggestions.clear();

			if (args.empty()) break;
			if (strlen(line) == 0) break;

			for (const auto& command : this->commands) {
				if (command->getName().find(args[0]) == 0) {
					this->suggestions.emplace_back(command->getName());
				}
			}

			break;
		}

		case ImGuiInputTextFlags_CallbackCompletion: {
			if (this->suggestions.empty()) {
//				addLog(false, "\n No suggestions found for '%s'\n\n", word.c_str());
			} else if (this->suggestions.size() == 1) {
				std::string suggestion = this->suggestions[0];
				suggestion.append(" ");

				data->DeleteChars(0, data->BufTextLen);
				data->InsertChars(0, suggestion.c_str());

				this->suggestions.clear();
			} else {
				std::string word = args[0];

				for (const auto& suggestion : this->suggestions) {
					if (suggestion.find(word) == 0) {
						data->DeleteChars(0, data->BufTextLen);
						data->InsertChars(0, suggestion.c_str());
						break;
					}
				}

				this->suggestions.clear();
			}

			break;
		}

		case ImGuiInputTextFlags_CallbackHistory: {
			const int prev_history_pos = this->historyPos;

			if (data->EventKey == ImGuiKey_UpArrow) {
				if (this->historyPos == -1) {
					this->historyPos = static_cast<int>(history.size()) - 1;
				} else if (historyPos > 0) {
					this->historyPos--;
				}
			} else if (data->EventKey == ImGuiKey_DownArrow && this->historyPos != -1 && ++this->historyPos >= static_cast<int>(history.size())) {
				this->historyPos = -1;
			}

			if (prev_history_pos != this->historyPos) {
				const char* history_str = (this->historyPos >= 0) ? history[this->historyPos].c_str() : "";
				data->DeleteChars(0, data->BufTextLen);
				data->InsertChars(0, history_str);

				this->suggestions.clear();
			}

			break;
		}
	}

	return 0;
}