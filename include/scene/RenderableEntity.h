#pragma once

#include "model/Model.h"
#include "shader/Program.h"
#include "Transformation.h"
#include <string>
#include <glm/glm.hpp>
#include <functional>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <utility>
#include <vector>

class RenderableEntity {
    private:
        std::string name;
        Model* model = nullptr;
        Program* shaderProgram = nullptr;

        Transformation transformation = Transformation();
        glm::mat4 matrix = glm::mat4(1.0f);

        std::function<void(RenderableEntity*, double)> simulateFunction = nullptr;

        explicit RenderableEntity(const std::string& name);

    public:
        RenderableEntity(const std::string& name, Model* model, Program* shaderProgram);
        ~RenderableEntity();

        std::string getName() const;

        Model* getModel() const;
        Program* getShaderProgram() const;

        Transformation* getTransformation();
        void calculateTransformationMatrix();
        glm::mat4 getTransformationMatrix();

        glm::vec3 getPosition();
        glm::vec3 getRotation();
        glm::vec3 getScale();

        void simulate(double deltaTime);
        void draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

        class Builder {
            private:
                RenderableEntity* renderableEntity;

            public:
                explicit Builder(const std::string& name);

                Builder* setModel(Model* model);
                Builder* setShaderProgram(Program* shaderProgram);

                Builder* setTransformation(Transform::Composite* composite);
                Builder* setSimulateFunction(std::function<void(RenderableEntity*, float)> simulateFunction);

                RenderableEntity* build();
        };

        static Builder* createEntity(const std::string& name);
};