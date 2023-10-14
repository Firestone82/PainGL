#include "console/ConsoleHandler.h"

#include <utility>
#include "StringUtils.h"
#include "Engine.h"
#include <string>

ConsoleHandler::ConsoleHandler(std::string title) : title(std::move(title)) {
	memset(inputBuffer, 0, sizeof(inputBuffer));
	this->clearLog();

	Engine* engine = Engine::getInstance();
	engine->getEventHandler()->addListener(new Listener<KeyPressEvent>([=](KeyPressEvent* event) {
		if ((event->getKey() == GLFW_KEY_GRAVE_ACCENT || (event->getKey() == GLFW_KEY_ESCAPE && isShown())) && event->getAction() == GLFW_PRESS) {
			this->setShown(!this->isShown());
		}
	}));

	addCommand(ConsoleCommand::createCommand("help")
			->setDescription("Displays all available commands")
			->setUsage("help")
			->setCallback([=](const std::vector<std::string>& args) {
				addLog(false,"\n Commands:");

				for (const auto& command : commands) {
					addLog(false,"  » %s", command->getUsage().c_str());
					addLog(false,"     # %s", command->getDescription().c_str());
				}
			})
			->build());

	addCommand(ConsoleCommand::createCommand("clear")
			->setDescription("Clears the console")
			->setUsage("clear")
			->setCallback([=](const std::vector<std::string>& args) {
				this->clearLog();
			})
			->build());

	addCommand(ConsoleCommand::createCommand("position")
		->setDescription("Sets the position of the camera")
		->setUsage("position <x> <y> <z>")
		->setMinArgs(3)
		->setMaxArgs(3)
		->setCallback([=](const std::vector<std::string>& args) {
			float x = 0.0;
			float y = 0.0;
			float z = 0.0;

			try {
				x = std::stof(args[1]);
				y = std::stof(args[2]);
				z = std::stof(args[3]);
			} catch (std::exception& e) {
				addLog(false, "[error] %s", e.what());
				return;
			}

			engine->getScene()->getCameraHandler()->getCamera()->setPosition(glm::vec3(x, y, z));
			engine->getScene()->getCameraHandler()->getCamera()->calculateViewMatrix();

			addLog(false,"\n Camera position set to (%0.2f, %0.2f, %0.2f)", x, y, z);
		})
		->build());

	addCommand(ConsoleCommand::createCommand("target")
		->setDescription("Sets the target of the camera")
		->setUsage("target <x> <y> <z>")
		->setMinArgs(3)
		->setMaxArgs(3)
		->setCallback([=](const std::vector<std::string>& args) {
			float x = 0.0;
			float y = 0.0;
			float z = 0.0;

			try {
				x = std::stof(args[1]);
				y = std::stof(args[2]);
				z = std::stof(args[3]);
			} catch (std::exception& e) {
				addLog(false, "[error] %s", e.what());
				return;
			}

		   engine->getScene()->getCameraHandler()->getCamera()->setTarget(glm::vec3(x, y, z));
		   engine->getScene()->getCameraHandler()->getCamera()->calculateViewMatrix();

		   addLog(false, "\n Camera target set to (%0.2f, %0.2f, %0.2f)", x, y, z);
		})
		->build());

	addCommand(ConsoleCommand::createCommand("sensitivity")
		->setDescription("Sets the sensitivity of the camera")
		->setUsage("sensitivity <sensitivity>")
		->setMinArgs(0)
		->setMaxArgs(1)
		->setCallback([=](const std::vector<std::string>& args) {
			float sensitivity = engine->getScene()->getCameraHandler()->getSensitivity();

			if (args.size() == 1) {
				addLog(false, "\n Camera sensitivity is %0.2f", sensitivity);
				return;
			}

			try {
				sensitivity = std::stof(args[1]);
				engine->getScene()->getCameraHandler()->setSensitivity(sensitivity);
			} catch (std::exception& e) {
				addLog(false, "[error] %s", e.what());
				return;
			}

			addLog(false, "\n Camera sensitivity set to %0.2f", sensitivity);
		})
		->build());

	addCommand(ConsoleCommand::createCommand("speed")
		->setDescription("Sets the speed of the camera")
		->setUsage("speed <speed>")
		->setMinArgs(0)
		->setMaxArgs(1)
		->setCallback([=](const std::vector<std::string>& args) {
			float speed = engine->getScene()->getCameraHandler()->getSpeed();

			if (args.empty() == 1) {
				addLog(false, "\n Camera speed is %0.2f", speed);
				return;
			}

			try {
				speed = std::stof(args[1]);
				engine->getScene()->getCameraHandler()->setSpeed(speed);
			} catch (std::exception& e) {
				addLog(false, "[error] %s", e.what());
				return;
			}

			addLog(false, "\n Camera speed set to %0.2f", speed);
		})
		->build());

	addCommand(ConsoleCommand::createCommand("fov")
		->setDescription("Sets the field of view of the camera")
		->setUsage("fov <fov>")
		->setMinArgs(0)
		->setMaxArgs(1)
		->setCallback([=](const std::vector<std::string>& args) {
			float fov = engine->getScene()->getCameraHandler()->getFov();

			if (args.size() == 1) {
				addLog(false, "\n Camera fov is %0.2f", fov);
				return;
			}

			try {
				fov = std::stof(args[1]);
				engine->getScene()->getCameraHandler()->setFov(fov);
				engine->getScene()->getCameraHandler()->calculateProjectionMatrix();
			} catch (std::exception& e) {
				addLog(false, "[error] %s", e.what());
				return;
			}

			addLog(false, "\n Camera fov set to %0.2f", fov);
		})
		->build());

	// TODO: Max FPS command

	// TODO: Static delta time command

	addCommand(ConsoleCommand::createCommand("demo")
		->setDescription("Toggle demo window")
		->setUsage("demo")
		->setCallback([=](const std::vector<std::string>& args) {
			bool state = engine->getGUIHandler()->isDemoShown();

			Engine *engine = Engine::getInstance();
			engine->getGUIHandler()->setDemoShow(!state);
			engine->getScene()->getCameraHandler()->setMoving(false);

			if (!state) {
				this->showConsole = false;
			}

			addLog(false, "\n Demo window %s", state ? "hidden" : "shown");
		})
		->build());

	addCommand(ConsoleCommand::createCommand("vsync")
		->setDescription("Toggle vsync between 20fps, 30fps, 60fps and unlimited")
		->setUsage("vsync <0,1,2,3>")
        ->setMinArgs(1)
        ->setMaxArgs(1)
		->setCallback([=](const std::vector<std::string>& args) {
			float sync = 0.0;

			try {
				sync = std::stof(args[1]);
			} catch (std::exception& e) {
				addLog(false, "[error] %s", e.what());
				return;
			}

			if (sync < 0 || sync > 3) {
				addLog(false, "[error] Vsync must be 0, 1, 2 or 3");
				return;
			}

			glfwSwapInterval(sync);
			int fps = (float) 60 / sync;

			addLog(false, "\n Vsync changed to %d (%dfps)", static_cast<int>(sync), (fps == 0 ? 2000 : fps));
		})
		->build());

	addCommand(ConsoleCommand::createCommand("gui")
		->setDescription("Toggle GUI from rendering")
		->setUsage("gui")
		->setCallback([=](const std::vector<std::string>& args) {
			bool state = engine->getGUIHandler()->isShown();
			engine->getGUIHandler()->setShow(!state);

			addLog(false, "\n GUI %s", state ? "disabled" : "enabled");
		})
		->build());
}

ConsoleHandler::~ConsoleHandler() {
	this->clearLog();
}

void ConsoleHandler::addLog(bool command, const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);

	char buf[1024];
	vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
	buf[IM_ARRAYSIZE(buf) - 1] = 0;
	this->log.emplace_back(new ConsoleLine(strdup(buf), command));

	va_end(args);
}

void ConsoleHandler::clearLog() {
	for (const auto& line : log) {
		delete line;
	}

	log.clear();
	historyPos = -1;
	memset(inputBuffer, 0, sizeof(inputBuffer));
}

static bool reclaim_focus = false;
void ConsoleHandler::setShown(bool show) {
	this->showConsole = show;

	Engine* engine = Engine::getInstance();
	static bool lastState = false;

	if (show) {
		lastState = engine->getScene()->getWindowHandler()->isCursorEnabled();
		engine->getScene()->getWindowHandler()->setCursorEnabled(true);

		ImGui::SetWindowFocus(title.c_str());
		reclaim_focus = true;
	} else {
		engine->getScene()->getWindowHandler()->setCursorEnabled(lastState);
	}
}

bool ConsoleHandler::isShown() const {
	return this->showConsole;
}

void ConsoleHandler::render() {
	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(title.c_str(), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings)) {
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
				static const float timestamp_width = ImGui::CalcTextSize("00:00:00").x;
				ImGui::SameLine(ImGui::GetColumnWidth(-1) - timestamp_width);

				ImGui::PushStyleColor(ImGuiCol_Text, {0.3f, 0.3f, 0.3f, 1.0f});
				ImGui::Text("%02d:%02d:%02d", ((item->getTimestamp() / 1000 / 3600) % 24), ((item->getTimestamp() / 1000 / 60) % 60), ((item->getTimestamp() / 1000) % 60));
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
	ImGui::InputText("##Input", inputBuffer, IM_ARRAYSIZE(inputBuffer), input_text_flags, &textEditCallbackStub, (void*) this);

	// Suggestions
	if (!suggestions.empty()) {
		ImGui::SetNextWindowPos({ImGui::GetItemRectMin().x, ImGui::GetItemRectMax().y});

		ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoMouseInputs;
		if (ImGui::Begin("TooltipCommands", nullptr, flags)) {
			for (const auto& suggestion : suggestions) {
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
		char* s = inputBuffer;
		while (*s == ' ') s++;

		executeCommand(s);
		suggestions.clear();

		memset(inputBuffer, 0, sizeof(inputBuffer));
		reclaim_focus = true;
	}

	// Clear console button
	ImGui::SameLine();
	if (ImGui::Button("Clear")) {
		clearLog();
	}

	ImGui::End();
}

static bool firstCommand = false;
void ConsoleHandler::executeCommand(const char *command_line) {

	// Add to log
	if (firstCommand) addLog(false,"");
	addLog(true,"> %s\n", command_line);
	firstCommand = true;

	// Add to history
	historyPos = -1;
	history.erase(std::remove(history.begin(), history.end(), command_line), history.end());
	history.emplace_back(strdup(command_line));

	// Parse arguments from command line
	std::vector<std::string> args = split(command_line, " ");
	args.erase(std::remove_if(args.begin(), args.end(), [](const std::string& arg) {
		return arg.empty();
	}), args.end());
	int argc = static_cast<int>(args.size()) - 1;

	// Process command
	for (const auto& command : commands) {
		if (strcasecmp(command->getName().c_str(), args[0].c_str()) == 0) {
			if (argc < command->getMinArgs() || argc > command->getMaxArgs()) {
				addLog(false,"\n[error] Wrong usage! Use: %s ", command->getUsage().c_str());
				return;
			}

			command->execute(args);
			return;
		}
	}

	addLog(false,"\n Unknown command: '%s'", command_line);
}

void ConsoleHandler::addCommand(ConsoleCommand* command) {
	commands.emplace_back(command);
}

int ConsoleHandler::textEditCallbackStub(ImGuiInputTextCallbackData* data) {
	auto textEditCallbackLambda = [=](ImGuiInputTextCallbackData* data) {
		ConsoleHandler* console = static_cast<ConsoleHandler*>(data->UserData);
		return console->textEditCallback(data);
	};

	return textEditCallbackLambda(data);
}

int ConsoleHandler::textEditCallback(ImGuiInputTextCallbackData* data) {
	const char* line = data->Buf;

	// Remove trailing and leading spaces
	while (*line == ' ') line++;
	char* line_end = (char*) line + strlen(line);
	while (line_end > line && line_end[-1] == ' ') line_end--;

	std::vector<std::string> args = split(line, " ");

	switch (data->EventFlag) {
		case ImGuiInputTextFlags_CallbackEdit: {
			this->suggestions.clear();

			if (args.empty()) break;
			if (strlen(line) == 0) break;

			for (const auto& command : commands) {
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
			const int prev_history_pos = historyPos;

			if (data->EventKey == ImGuiKey_UpArrow) {
				if (historyPos == -1) {
					historyPos = static_cast<int>(history.size()) - 1;
				} else if (historyPos > 0) {
					historyPos--;
				}
			} else if (data->EventKey == ImGuiKey_DownArrow && historyPos != -1 && ++historyPos >= static_cast<int>(history.size())) {
				historyPos = -1;
			}

			if (prev_history_pos != historyPos) {
				const char* history_str = (historyPos >= 0) ? history[historyPos].c_str() : "";
				data->DeleteChars(0, data->BufTextLen);
				data->InsertChars(0, history_str);

				this->suggestions.clear();
			}

			break;
		}
	}

	return 0;
}