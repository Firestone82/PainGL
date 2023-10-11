#include "Scene.h"

Scene::Scene(int width, int height, const char* title) {
    this->window = new Window(width, height, title);
}

Scene::~Scene() {
    delete this->window;
}

void Scene::renderEntity(RenderableEntity* entity) {
    this->entities.push_back(entity);
}

void Scene::draw() {
    // Projection matrix
    glm::mat4 projection = glm::perspective(
            glm::radians(this->fieldOfView),           // 45° Field of View
            this->aspectRatio,                                // 4:3 ratio
            this->nearFarPlane.x, this->nearFarPlane.y); // display range : 0.1 unit <-> 100 units

    // Camera matrix
    glm::mat4 view = glm::lookAt(
            glm::vec3(0.003, 15, 0), // Camera is at (4,3,-3), in World Space
            glm::vec3(0, 0, 0),    // and looks at the origin
            glm::vec3(0, 1, 0)        // Head is up (set to 0,-1,0 to look upside-down)
    );

    for (const auto &entity: this->entities) {
        entity->calculateTransformationMatrix();
        entity->draw(view, projection);
    }
}

void Scene::tick(double deltaTime) {
    for (const auto &entity: this->entities) {
        entity->simulate(deltaTime);
    }
}

void Scene::setFieldOfView(float fieldOfView) {
    this->fieldOfView = fieldOfView;
}

float Scene::getFieldOfView() const {
    return this->fieldOfView;
}

void Scene::setAspectRatio(float aspectRatio) {
    this->aspectRatio = aspectRatio;
}

float Scene::getAspectRatio() const {
    return this->aspectRatio;
}

void Scene::setNearFarPlane(glm::vec2 nearFarPlane) {
    this->nearFarPlane = nearFarPlane;
}

glm::vec2 Scene::getNearFarPlane() const {
    return this->nearFarPlane;
}

Window* Scene::getWindow() {
    return this->window;
}

const std::vector<RenderableEntity*>& Scene::getEntities() {
    return this->entities;
}