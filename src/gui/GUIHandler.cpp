#include "GUIHandler.h"
#include "../engine/Engine.h"

void draw(Transform::Composite* trans, int indent = 0);
void drawTooltip(Transform::Component* t);

GUIHandler::GUIHandler(Window* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window->get(), true);
    ImGui_ImplOpenGL3_Init();
}

GUIHandler::~GUIHandler() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GUIHandler::handle() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUIHandler::render() {
    int height = Engine::getInstance()->getScene()->getWindow()->getHeight();

//    ImGui::ShowDemoWindow();

    int frameFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
    ImGui::Begin("Frames", nullptr, frameFlags);
    ImGui::SetWindowPos(ImVec2(15, 15));
    ImGui::Text("Frame Rate: %0.2f fps", ImGui::GetIO().Framerate);
    ImGui::Text("Frame Time: %0.3f ms", 1000.0f / ImGui::GetIO().Framerate);
    ImGui::Text("Delta Time: %0.5f ns", Engine::getInstance()->getDeltaTime());
    ImGui::End();

    ImGui::Begin("Entities", nullptr, ImGuiWindowFlags_NoSavedSettings);
    ImGui::SetWindowPos(ImVec2(15, 95), ImGuiCond_FirstUseEver);
    ImGui::SetWindowSize(ImVec2(0, 0));

    bool first = true;
    for (RenderableEntity* entity : Engine::getInstance()->getScene()->getEntities()) {
        char name[256];
        sprintf(name, "Entity: %s", entity->getName().c_str());

        if (ImGui::TreeNodeEx(name, first ? ImGuiTreeNodeFlags_DefaultOpen : 0)) {
            first = false;

            // Draw Transformation
            if (ImGui::BeginTable("entityTable", 4, ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody)) {
                ImGui::TableSetupColumn("property", ImGuiTableColumnFlags_WidthFixed, 65.0f);

                ImGui::TableNextColumn();
                ImGui::Text("Position");
                for (int i = 0; i < 3; i++) {
                    ImGui::TableNextColumn();
                    ImGui::Text("%7.2f", entity->getPosition()[i]);
                }

                ImGui::TableNextColumn();
                ImGui::Text("Rotation");
                for (int i = 0; i < 3; i++) {
                    ImGui::TableNextColumn();
                    ImGui::Text("%7.2f", entity->getRotation()[i]);
                }

                ImGui::TableNextColumn();
                ImGui::Text("Scale");
                for (int i = 0; i < 3; i++) {
                    ImGui::TableNextColumn();
                    ImGui::Text("%7.2f", entity->getScale()[i]);
                }

                ImGui::EndTable();
            }

            // Draw Properties
            if (ImGui::TreeNodeEx("Properties")) {
                if (ImGui::BeginTable("entityTable2", 2, ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody)) {
                    ImGui::TableSetupColumn("property", ImGuiTableColumnFlags_WidthFixed, 100.0f);

                    ImGui::TableNextColumn();
                    ImGui::Text("Vertex Count");
                    ImGui::TableNextColumn();
                    ImGui::Text("%lld", entity->getModel()->getPoints().size());

                    ImGui::TableNextColumn();
                    ImGui::Text("Indices Count");
                    ImGui::TableNextColumn();
                    ImGui::Text("%lld", entity->getModel()->getIndices().size());

                    ImGui::TableNextColumn();
                    ImGui::Text("Shader Program");
                    ImGui::TableNextColumn();
                    ImGui::Text("%s", entity->getShaderProgram()->toString().c_str());

                    ImGui::EndTable();
                }

                ImGui::TreePop();
            }

            // Draw Transformation
            if (ImGui::TreeNodeEx("Transformations")) {
                if (ImGui::BeginTable("transformationTable", 1, ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody)) {
                    if (entity->getTransformation()->get()->isEmpty()) {
                        ImGui::TableNextColumn();
                        ImGui::Text("No transformations");
                    } else {
                        draw(entity->getTransformation()->get(), 0);

                        ImGui::TableNextColumn();
                        ImGui::Text("=> Result matrix:");
                        drawTooltip(entity->getTransformation()->get());
                    }

                    ImGui::EndTable();
                }

                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
    }

    ImGui::End();

    int authorFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
    ImGui::Begin("Author", nullptr, authorFlags);
    ImGui::SetWindowPos(ImVec2(15, height - 65));
    ImGui::Text("Author: Pavel Mikula, MIK0486");
    ImGui::Text("Version: 1.0.0");
    ImGui::End();
}

void draw(Transform::Composite* trans, int indent) {
    for (Transform::Component* t : trans->get()) {
        if (indent > 0) {
            ImGui::Indent(indent * 20.0f);
        }

        ImGui::TableNextColumn();

        if (t->getType() == Transform::Type::COMPOSITE) {
            ImGui::Text("-> Composite:");

            indent++;
            drawTooltip(t);
            draw((Transform::Composite*) t, indent);
            indent--;
        }

        if (t->getType() == Transform::Type::TRANSLATE) {
            Transform::Translate* translate = (Transform::Translate*) t;

            ImGui::Text("-> Translate: (%0.2f, %0.2f, %0.2f)", translate->getVector().x, translate->getVector().y, translate->getVector().z);
            drawTooltip(t);
        }

        if (t->getType() == Transform::Type::ROTATE) {
            Transform::Rotation* rotate = (Transform::Rotation*) t;
            ImGui::Text("-> Rotate: (%0.2f, %0.2f, %0.2f)", rotate->getVector().x, rotate->getVector().y, rotate->getVector().z);
            drawTooltip(t);
        }

        if (t->getType() == Transform::Type::SCALE) {
            Transform::Scale* scale = (Transform::Scale*) t;
            ImGui::Text("-> Scale: (%0.2f, %0.2f, %0.2f)", scale->getVector().x, scale->getVector().y, scale->getVector().z);
            drawTooltip(t);
        }

        if (indent > 0) {
            ImGui::Unindent(indent * 20.0f);
        }
    }
}

void drawTooltip(Transform::Component* t) {
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();

        ImGui::Text("Matrix:");
        glm::mat4 mat = t->resultMatrix();

        if (ImGui::BeginTable("matrixTable", 4, ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody)) {
            for (int x = 0; x < 4; x++) {
                ImGui::TableNextRow();

                for (int y = 0; y < 4; y++) {
                    ImGui::TableNextColumn();

                    if (mat[x][y] == 0.0f) {
                        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(200, 200, 200, 200));
                    } else {
                        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
                    }

                    ImGui::Text("%0.2f", mat[x][y]);
                    ImGui::PopStyleColor();
                }
            }

            ImGui::EndTable();
        }

        ImGui::EndTooltip();
    }
}

void GUIHandler::clear() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}