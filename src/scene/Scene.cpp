#include "Scene.h"
#include <glm/gtc/matrix_transform.hpp>

Scene::Scene(int width, int height, const char* title) {
    this->window = new Window(width, height, title);
}

Scene::~Scene() {
    delete this->window;
}

void Scene::renderEntity(RenderableEntity* entity) {
    this->entities.push_back(entity);
}

void Scene::draw(double deltaTime) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 projection = glm::perspective(
            glm::radians(this->fieldOfView),
            this->aspectRatio,
            this->nearFarPlane.x, this->nearFarPlane.y);

    // Camera matrix
    glm::mat4 view = glm::lookAt(
            glm::vec3(0, 0, 4), // Camera is at (4,3,-3), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    for (auto& entity : this->entities) {
        entity->draw(projection * view * entity->getTransformationMatrix());
    }

    glfwSwapBuffers(window->get());
}

void Scene::simulate(double deltaTime) {
    for (auto& entity : this->entities) {
        entity->setRotation(
                entity->getRotation().x,
                entity->getRotation().y + 90.0f * deltaTime,
                entity->getRotation().z
        );
    }

//    std::cout << "Simulate.. " << deltaTime << std::endl;
}

float Scene::setFieldOfView(float fieldOfView) {
    this->fieldOfView = fieldOfView;
    return this->fieldOfView;
}

float Scene::getFieldOfView() const {
    return this->fieldOfView;
}

float Scene::setAspectRatio(float aspectRatio) {
    this->aspectRatio = aspectRatio;
    return this->aspectRatio;
}

float Scene::getAspectRatio() const {
    return this->aspectRatio;
}

glm::vec2 Scene::setNearFarPlane(glm::vec2 nearFarPlane) {
    this->nearFarPlane = nearFarPlane;
    return this->nearFarPlane;
}

glm::vec2 Scene::getNearFarPlane() const {
    return this->nearFarPlane;
}

Window* Scene::getWindow() {
    return this->window;
}