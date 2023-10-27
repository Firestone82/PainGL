#include <thread>
#include "3rdparty/imgui/imgui.h"
#include "3rdparty/imgui/backend/imgui_impl_opengl3.h"
#include "3rdparty/imgui/backend/imgui_impl_glfw.h"
#include "gui/GUIHandler.h"
#include "Engine.h"

GUIHandler::GUIHandler() {
	this->fillGUIs();
}

GUIHandler::~GUIHandler() {
	for (const auto &gui: this->guis) {
		delete gui;
	}

	this->guis.clear();
}

void GUIHandler::handle() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GUIHandler::render() {
	float topPadding = 15.0f;

	for (const auto& gui: this->guis) {
		gui->render(topPadding);
	}

	if (this->showDemo) {
		ImGui::ShowDemoWindow(&this->showDemo);
	}
}

void GUIHandler::clear() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIHandler::addGUI(GUI* gui) {
	this->guis.push_back(gui);
}

void GUIHandler::removeGUI(GUI* gui) {
	this->guis.erase(std::remove(this->guis.begin(), this->guis.end(), gui), this->guis.end());
}

void GUIHandler::setEnabled(bool enable) {
	this->showGui = enable;
}

bool GUIHandler::isEnabled() const {
	return this->showGui;
}

void GUIHandler::setDemoEnabled(bool enable) {
	this->showDemo = enable;
}

bool GUIHandler::isDemoEnabled() const {
	return this->showDemo;
}