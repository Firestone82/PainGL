#pragma once

#include "../../buffer/VAO.h"
#include "../../buffer/VBO.h"
#include "../../buffer/EBO.h"
#include <string>
#include <glm/glm.hpp>

class Model {
    private:
        std::string name;
        bool object = false;

        VAO* vao;
        VBO* vbo;
        EBO* ebo;

        std::vector<float> data;
        std::vector<unsigned int> indices;
        GLint size;

    public:
        Model(const std::string &name, const std::vector<float>& data, GLint size);
        Model(const std::string &name, const std::vector<float>& data, const std::vector<unsigned int>& indices, GLint size);
        ~Model();

        std::string getName() const;
        bool hasIndices() const;

        VAO* getVAO() const;
        VBO* getVBO() const;
        EBO* getEBO() const;

        std::vector<float> getData() const;
        GLint getSize() const;

        GLsizei getVerticesCount() const;
};
