#pragma once

#include "../../buffer/VAO.h"
#include "../../buffer/VBO.h"
#include <string>
#include <glm/glm.hpp>

class Model {
    private:
        std::string name;

        VAO* vao;
        VBO* vbo;
        int dataSize;
        int vertexCount;

    public:
        Model(const std::string& name, const float* data, int dataSize, int vertexCount);
        ~Model();

        std::string getName() const;
        VAO* getVAO() const;
        VBO* getVBO() const;
        int getDataSize() const;
        int getVertexCount() const;
};
