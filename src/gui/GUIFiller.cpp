#include "gui/GUIHandler.h"
#include "Engine.h"

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

void drawEntityTransformation(Transform::Composite* trans, float indent = 0)  {
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

void GUIHandler::fillGUIs() {
	Engine* engine = Engine::getInstance();
	int defaultFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;

	this->guis.emplace_back(new GUI("Frames", [=](GUI* gui, float &top) {
		ImGui::Begin(gui->getName().c_str(), nullptr, defaultFlags | ImGuiWindowFlags_NoTitleBar);
		ImGui::SetWindowPos(ImVec2(15.0f, top));

		Scene* activeScene = engine->getSceneHandler()->getActiveScene();
		ImGui::Text("Scene: %s (#%d)", activeScene->getName().c_str(), activeScene->getID());
		ImGui::Separator();
		ImGui::Text("Frame Rate: %0.2f fps (%0.3f ms)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
		ImGui::Text("Delta Time: %0.5f ns", engine->getDeltaTime());

		top += ImGui::GetWindowHeight() + 15;
		ImGui::End();
	}));

	this->guis.emplace_back(new GUI("Camera", [=](GUI* gui, float &top) {
		Scene* scene = engine->getSceneHandler()->getActiveScene();
		if (scene == nullptr) return;

		ImGui::Begin(gui->getName().c_str(), nullptr, defaultFlags | (engine->getWindowHandler()->isCursorEnabled() ? 0 : ImGuiWindowFlags_NoMouseInputs) | ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::SetWindowPos(ImVec2(15.0f,top));

		if (ImGui::BeginTable("cameraTable", 4, ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody)) {
			ImGui::TableSetupColumn("property", ImGuiTableColumnFlags_WidthFixed, 65.0f);

			ImGui::TableNextColumn();
			ImGui::Text("Position");
			for (int i = 0; i < 3; i++) {
				ImGui::TableNextColumn();
				ImGui::Text("%7.2f", scene->getCameraHandler()->getCamera()->getPosition()[i]);
			}

			ImGui::TableNextColumn();
			ImGui::Text("Target");
			for (int i = 0; i < 3; i++) {
				ImGui::TableNextColumn();
				ImGui::Text("%7.2f", scene->getCameraHandler()->getCamera()->getTarget()[i]);
			}

			ImGui::EndTable();
		}

		ImGui::Text("Rotation: %7.2f Pitch / %7.2f Yaw", scene->getCameraHandler()->getCamera()->getPitch(), scene->getCameraHandler()->getCamera()->getYaw());
		ImGui::Text("Resolution: %d x %d", engine->getWindowHandler()->getWidth(), engine->getWindowHandler()->getHeight());

		ImGui::Separator();

		int windowHeight = engine->getWindowHandler()->getHeight();
		int windowWidth = engine->getWindowHandler()->getWidth();
		Object* crosshairObject = scene->getObjectAt(windowWidth / 2, windowHeight / 2);

		if (crosshairObject != nullptr) {
			AbstractLight* light = dynamic_cast<AbstractLight*>(crosshairObject);
			if (light) {
				ImGui::Text("Target: Light  - %s (#%d)", light->getName().c_str(), light->getID());
			} else {
				Entity* entity = dynamic_cast<Entity*>(crosshairObject);

				if (entity) {
					ImGui::Text("Target: Entity - %s (#%d)", entity->getName().c_str(), entity->getID());
				} else {
					ImGui::Text("Target: NaN");
				}
			}
		} else {
			ImGui::Text("Target: NaN");
		}

		if (engine->getWindowHandler()->isCursorEnabled()) {
			int posX = engine->getEventHandler()->getInputController()->getMousePosition().x;
			int posY = engine->getEventHandler()->getInputController()->getMousePosition().y;
			Object* cursorObject = scene->getObjectAt(posX, engine->getWindowHandler()->getHeight() - posY);

			AbstractLight* light = dynamic_cast<AbstractLight*>(cursorObject);
			if (light) {
				ImGui::Text("Cursor: Light - %s (#%d)", light->getName().c_str(), light->getID());
			} else {
				Entity* entity = dynamic_cast<Entity*>(cursorObject);

				if (entity) {
					ImGui::Text("Cursor: Entity - %s (#%d)", entity->getName().c_str(), entity->getID());
				} else {
					ImGui::Text("Cursor: NaN");
				}
			}
		}

		top += ImGui::GetWindowHeight() + 15;
		ImGui::End();
	}));

	this->guis.emplace_back(new GUI("Entities", [=](GUI* gui, float &top) {
		Scene* scene = engine->getSceneHandler()->getActiveScene();
		if (scene == nullptr) return;

		// If window would be out of screen, move it to the right
		int flags = defaultFlags | (engine->getWindowHandler()->isCursorEnabled() ? 0 : ImGuiWindowFlags_NoMouseInputs);

		if (scene->getEntityHandler()->getEntities().size() < 10) {
			flags = flags | ImGuiWindowFlags_AlwaysAutoResize;
		} else {
			ImGui::SetNextWindowSize(ImVec2(0, 300));
		}

		ImGui::Begin(gui->getName().c_str(), nullptr, flags);
		ImGui::SetWindowPos(ImVec2(15, top));

		static bool first = true;
		for (Entity* entity: scene->getEntityHandler()->getEntities()) {
			char name[256];
			sprintf(name, "Entity: %s (#%d)  ", entity->getName().c_str(), entity->getID());

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
						ImGui::Text("%lld", entity->getModel()->getMesh(0)->getVertices().size());

						ImGui::TableNextColumn();
						ImGui::Text("Indices Count");
						ImGui::TableNextColumn();
						ImGui::Text("%lld", entity->getModel()->getMesh(0)->getIndices().size());

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

		top += ImGui::GetWindowHeight() + 15;
		ImGui::End();
	}));

	this->guis.emplace_back(new GUI("Lights", [=](GUI* gui, float &top) {
		Scene* scene = engine->getSceneHandler()->getActiveScene();
		if (scene == nullptr) return;

		if (scene->getLightHandler()->getLights().empty()) return;

		ImGui::Begin(gui->getName().c_str(), nullptr, defaultFlags | (engine->getWindowHandler()->isCursorEnabled() ? 0 : ImGuiWindowFlags_NoMouseInputs) | ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::SetWindowPos(ImVec2(15, top));

		static bool first = true;
		for (AbstractLight* light: scene->getLightHandler()->getLights()) {
			char name[256];
			sprintf(name, "Color: %s (#%d)", light->getName().c_str(), light->getID());

			if (ImGui::TreeNodeEx(name, first ? ImGuiTreeNodeFlags_DefaultOpen : 0)) {
				first = false;

//				ImVec4 color = ImVec4(light->getColor().x, light->getColor().y, light->getColor().z, 1.0f);
//				ImGui::ColorButton("##color", color, ImGuiColorEditFlags_NoPicker, ImVec2(15, 15));

				// Draw Transformation
				if (ImGui::TreeNodeEx("Transformations")) {
					if (ImGui::BeginTable("entityTable", 4, ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody)) {
						ImGui::TableSetupColumn("property", ImGuiTableColumnFlags_WidthFixed, 65.0f);

//						Renderable* renderable = dynamic_cast<Renderable*>(light);
//
//						ImGui::TableNextColumn();
//						ImGui::Text("Position");
//						for (int i = 0; i < 3; i++) {
//							ImGui::TableNextColumn();
//							ImGui::Text("%7.2f", renderable->getPosition()[i]);
//						}
//
//						ImGui::TableNextColumn();
//						ImGui::Text("Rotation");
//						for (int i = 0; i < 3; i++) {
//							ImGui::TableNextColumn();
//							ImGui::Text("%7.2f", renderable->getRotation()[i]);
//						}
//
//						ImGui::TableNextColumn();
//						ImGui::Text("Scale");
//						for (int i = 0; i < 3; i++) {
//							ImGui::TableNextColumn();
//							ImGui::Text("%7.2f", renderable->getScale()[i]);
//						}

						ImGui::EndTable();
					}

					ImGui::TreePop();
				}

				// Draw Transformation
//				if (ImGui::TreeNodeEx("Transformations")) {
//					if (ImGui::BeginTable("transformationTable", 1, ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody)) {
//						if (light->getTransformation()->get()->isEmpty()) {
//							ImGui::TableNextColumn();
//							ImGui::Text("No transformations");
//						} else {
//							ImGui::TableNextColumn();
//							ImGui::Text("Composite:");
//							drawTransformationMatrix(light->getTransformation()->get()->resultMatrix());
//							drawEntityTransformation(light->getTransformation()->get(), 0);
//						}
//
//						ImGui::EndTable();
//					}
//
//					ImGui::TreePop();
//				}

				ImGui::TreePop();
			}
		}

		top += ImGui::GetWindowHeight() + 15;
		ImGui::End();
	}));

	this->guis.emplace_back(new GUI("Crosshair", [=](GUI* gui, float &top) {
		float height = float(engine->getWindowHandler()->getHeight());
		float width = float(engine->getWindowHandler()->getWidth());

		ImGui::Begin(gui->getName().c_str(), nullptr, defaultFlags | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs);
		ImGui::SetWindowPos(ImVec2(width / 2.0f - 5.0f, height / 2.0f - 5.0f));

		ImGui::Text("X");

		ImGui::End();
	}));

	this->guis.emplace_back(new GUI("Author", [=](GUI* gui, float &top) {
		ImGui::Begin(gui->getName().c_str(), nullptr, defaultFlags | ImGuiWindowFlags_NoTitleBar);
		ImGui::SetWindowPos(ImVec2(15, float(engine->getWindowHandler()->getHeight()) - ImGui::GetWindowHeight() - 15.0f));

		ImGui::Text("Author: Pavel Mikula, MIK0486");
		ImGui::Text("Version: 2.0.0");

		ImGui::End();
	}));
}