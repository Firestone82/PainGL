#pragma once

#include "../../model/model/Model.h"
#include "../../shader/program/Program.h"
#include <string>
#include <glm/glm.hpp>

class RenderableEntity {
    private:
        Model* model = nullptr;
        Program* shaderProgram = nullptr;

        glm::vec3 positionVector = glm::vec3(0.0f);
        glm::vec3 rotationVector = glm::vec3(0.0f);
        glm::vec3 scaleVector = glm::vec3(1.0f);

    public:
        RenderableEntity(Model* model, Program* shaderProgram);
        ~RenderableEntity();

        Model* getModel() const;
        Program* getShaderProgram() const;
        glm::mat4 getTransformationMatrix() const;

        glm::vec3 getPosition() const;
        void setPosition(float x, float y, float z);

        glm::vec3 getRotation() const;
        void setRotation(float x, float y, float z);

        glm::vec3 getScale() const;
        void setScale(float x, float y, float z);

        void draw(glm::mat4 modelView);

};
