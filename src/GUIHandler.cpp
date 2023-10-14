#include "GUIHandler.h"
#include "Engine.h"

float topPadding = 15.0f;

void drawTransformationMatrix(glm::mat4 mat)  {
	if (ImGui::IsItemHovered()) {
		ImGui::BeginTooltip();

		ImGui::Text("Matrix:");
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

void drawFrames() {
	int frameFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
	ImGui::Begin("Frames", nullptr, frameFlags);
	ImGui::SetWindowPos(ImVec2(15.0f, topPadding));

	ImGui::Text("Frame Rate: %0.2f fps (%0.3f ms)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
	ImGui::Text("Delta Time: %0.5f ns", Engine::getInstance()->getDeltaTime());

	topPadding += ImGui::GetWindowHeight() + 15;

	ImGui::End();
}

void drawCrosshair() {
	float height = Engine::getInstance()->getScene()->getWindowHandler()->getHeight();
	float width = Engine::getInstance()->getScene()->getWindowHandler()->getWidth();

	int crosshairFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs;
	ImGui::Begin("Crosshair", nullptr, crosshairFlags);
	ImGui::SetWindowPos(ImVec2(width / 2 - 5, height / 2 - 5));

	ImGui::Text("X");

	ImGui::End();
}

void drawAuthor() {
	int authorFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
	ImGui::Begin("Author", nullptr, authorFlags);
	ImGui::SetWindowPos(ImVec2(15, Engine::getInstance()->getScene()->getWindowHandler()->getHeight() - ImGui::GetWindowHeight() - 15));

	ImGui::Text("Author: Pavel Mikula, MIK0486");
	ImGui::Text("Version: 1.0.0");

	ImGui::End();
}

void drawCamera() {
	Engine* engine = Engine::getInstance();
	CameraHandler* cameraHandler = engine->getScene()->getCameraHandler();
	Camera* camera = cameraHandler->getCamera();

	int environmentFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | (engine->getScene()->getWindowHandler()->isCursorEnabled() ? 0 : ImGuiWindowFlags_NoMouseInputs);
	ImGui::Begin("Camera", nullptr, environmentFlags);
	ImGui::SetWindowPos(ImVec2(15.0f,topPadding));

	if (ImGui::BeginTable("cameraTable", 4, ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody)) {
		ImGui::TableSetupColumn("property", ImGuiTableColumnFlags_WidthFixed, 65.0f);

		ImGui::TableNextColumn();
		ImGui::Text("Position");
		for (int i = 0; i < 3; i++) {
			ImGui::TableNextColumn();
			ImGui::Text("%7.2f", camera->getPosition()[i]);
		}

		ImGui::TableNextColumn();
		ImGui::Text("Target");
		for (int i = 0; i < 3; i++) {
			ImGui::TableNextColumn();
			ImGui::Text("%7.2f", camera->getTarget()[i]);
		}

		ImGui::EndTable();
	}

	ImGui::Text("Rotation: %7.2f Pitch / %7.2f Yaw", camera->getPitch(), camera->getYaw());
	ImGui::Text("Resolution: %d x %d", engine->getScene()->getWindowHandler()->getWidth(), engine->getScene()->getWindowHandler()->getHeight());

	topPadding += ImGui::GetWindowHeight() + 15;

	ImGui::End();
}

void drawEntityTransformation(Transform::Composite* trans, int indent = 0)  {
	for (Transform::Component* t : trans->get()) {
		if (indent > 0) {
			ImGui::Indent(indent * 20.0f);
		}

		ImGui::TableNextColumn();

		if (t->getType() == Transform::Type::COMPOSITE) {
			ImGui::Text("-> Composite:");

			indent++;
			drawTransformationMatrix(t->resultMatrix());
			drawEntityTransformation((Transform::Composite*) t, indent);
			indent--;
		}

		if (t->getType() == Transform::Type::TRANSLATE) {
			Transform::Translate* translate = (Transform::Translate*) t;

			ImGui::Text("-> Translate: (%0.2f, %0.2f, %0.2f)", translate->getVector().x, translate->getVector().y, translate->getVector().z);
			drawTransformationMatrix(t->resultMatrix());
		}

		if (t->getType() == Transform::Type::ROTATE) {
			Transform::Rotation* rotate = (Transform::Rotation*) t;
			ImGui::Text("-> Rotate: (%0.2f, %0.2f, %0.2f)", rotate->getVector().x, rotate->getVector().y, rotate->getVector().z);
			drawTransformationMatrix(t->resultMatrix());
		}

		if (t->getType() == Transform::Type::SCALE) {
			Transform::Scale* scale = (Transform::Scale*) t;
			ImGui::Text("-> Scale: (%0.2f, %0.2f, %0.2f)", scale->getVector().x, scale->getVector().y, scale->getVector().z);
			drawTransformationMatrix(t->resultMatrix());
		}

		if (indent > 0) {
			ImGui::Unindent(indent * 20.0f);
		}
	}
}

void drawEntities() {
	Engine* engine = Engine::getInstance();

	ImGui::Begin("Entities", nullptr, ImGuiWindowFlags_NoSavedSettings | (engine->getScene()->getWindowHandler()->isCursorEnabled() ? 0 : ImGuiWindowFlags_NoMouseInputs) | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SetWindowPos(ImVec2(15, topPadding));

	static bool first = true;
	for (RenderableEntity* entity : engine->getScene()->getEntities()) {
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
						ImGui::TableNextColumn();
						ImGui::Text("Composite:");
						drawTransformationMatrix(entity->getTransformation()->get()->resultMatrix());

						drawEntityTransformation(entity->getTransformation()->get(), 0);
					}

					ImGui::EndTable();
				}

				ImGui::TreePop();
			}

			ImGui::TreePop();
		}
	}

	topPadding = ImGui::GetWindowHeight() + 15;

	ImGui::End();
}

GUIHandler::GUIHandler(WindowHandler* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window->getWindow(), true);
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
	topPadding = 15.0f;

    drawFrames();
	drawCamera();
	drawEntities();
	drawAuthor();
	drawCrosshair();
}

void GUIHandler::clear() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUIHandler::setShow(bool show) {
	this->showGui = show;
}

bool GUIHandler::isShown() const {
	return this->showGui;
}

void GUIHandler::setDemoShow(bool show) {
	this->showDemo = show;
}

bool GUIHandler::isDemoShown() const {
	return this->showDemo;
}