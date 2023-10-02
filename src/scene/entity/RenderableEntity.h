#pragma once

#include "../../model/model/Model.h"
#include "../../shader/program/Program.h"
#include <string>
#include <glm/glm.hpp>
#include <functional>

class RenderableEntity {
    private:
        std::string name;
        Model* model = nullptr;
        Program* shaderProgram = nullptr;

        glm::vec3 positionVector = glm::vec3(0.0f);
        glm::vec3 rotationVector = glm::vec3(0.0f);
        glm::vec3 scaleVector = glm::vec3(1.0f);

        std::function<void(RenderableEntity*, double)> simulateFunction = nullptr;

        explicit RenderableEntity(const std::string& name);

    public:
        RenderableEntity(const std::string& name, Model* model, Program* shaderProgram);
        ~RenderableEntity();

        std::string getName() const;

        Model* getModel() const;
        Program* getShaderProgram() const;

        glm::mat4 getTransformationMatrix() const;

        void setPosition(float x, float y, float z);
        glm::vec3 getPosition() const;

        void setRotation(float x, float y, float z);
        glm::vec3 getRotation() const;

        void setScale(float scale);
        void setScale(float x, float y, float z);
        glm::vec3 getScale() const;

        void simulate(double deltaTime);
        void draw(glm::mat4 modelView);

        class Builder {
            private:
                RenderableEntity* renderableEntity;

            public:
                explicit Builder(const std::string& name);

                Builder* setModel(Model* model);
                Builder* setShaderProgram(Program* shaderProgram);

                Builder* setPosition(float x, float y, float z);
                Builder* setRotation(float x, float y, float z);
                Builder* setScale(float scale);
                Builder* setScale(float x, float y, float z);

                Builder* setSimulateFunction(std::function<void(RenderableEntity*, float)> simulateFunction);

                RenderableEntity* build();
        };

        static Builder* createEntity(const std::string& name);
};