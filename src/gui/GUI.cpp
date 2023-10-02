#include "GUI.h"
#include "../engine/Engine.h"

GUI::GUI(Window* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window->get(), true);
    ImGui_ImplOpenGL3_Init();
}

GUI::~GUI() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GUI::handle() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUI::render() {
    ImGui::Begin("Frames", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);
    ImGui::SetWindowPos(ImVec2(15, 15));
    ImGui::Text("Frame Rate: %0.2f", ImGui::GetIO().Framerate);
    ImGui::Text("Frame Time: %0.2f ms", 1000.0f / ImGui::GetIO().Framerate);
    ImGui::End();

    // WATAFAK KDO TO NAPSAL, TO JE MOC FANCY
//    ImGui::ShowDemoWindow();

    static ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize;
    ImGui::Begin("Entities", nullptr, ImGuiWindowFlags_NoSavedSettings);
    ImGui::SetWindowSize(ImVec2(0, 0));
    ImGui::SetWindowPos(ImVec2(15, 75), ImGuiCond_FirstUseEver);

    bool first = true;
    for (RenderableEntity* entity : Engine::getInstance()->getScene()->getEntities()) {
        std::string name = "Entity: " + entity->getName();

        if (ImGui::TreeNodeEx(name.c_str(), first ? ImGuiTreeNodeFlags_DefaultOpen : 0)) {
            first = false;

            if (ImGui::BeginTable("entityTable", 4, ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody)) {
                ImGui::TableSetupColumn("property", ImGuiTableColumnFlags_WidthFixed, 100.0f);
                ImGui::TableSetupColumn("valueX", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("valueY", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("valueZ", ImGuiTableColumnFlags_WidthFixed);

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Position");
                ImGui::TableNextColumn();
                ImGui::Text("%0.2f", entity->getPosition().x);
                ImGui::TableNextColumn();
                ImGui::Text("%0.2f", entity->getPosition().y);
                ImGui::TableNextColumn();
                ImGui::Text("%0.2f", entity->getPosition().z);

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Rotation");
                ImGui::TableNextColumn();
                ImGui::Text("%0.2f", entity->getRotation().x);
                ImGui::TableNextColumn();
                ImGui::Text("%0.2f", entity->getRotation().y);
                ImGui::TableNextColumn();
                ImGui::Text("%0.2f", entity->getRotation().z);

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Scale");
                ImGui::TableNextColumn();
                ImGui::Text("%0.2f", entity->getScale().x);
                ImGui::TableNextColumn();
                ImGui::Text("%0.2f", entity->getScale().y);
                ImGui::TableNextColumn();
                ImGui::Text("%0.2f", entity->getScale().z);

                ImGui::EndTable();
            }

            if (ImGui::BeginTable("entityTable2", 2, ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody)) {
                ImGui::TableSetupColumn("property", ImGuiTableColumnFlags_WidthFixed, 100.0f);

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Vertex Count");
                ImGui::TableNextColumn();
                ImGui::Text("%d", entity->getModel()->getPoints().size());

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Indices Count");
                ImGui::TableNextColumn();
                ImGui::Text("%d", entity->getModel()->getIndices().size());

                ImGui::EndTable();
            }

            ImGui::TreePop();
        }
    }

    ImGui::End();
}

void GUI::clear() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}