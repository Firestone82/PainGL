#pragma once

#include "buffer/VAO.h"
#include "buffer/VBO.h"
#include "buffer/EBO.h"
#include "buffer/Vertex.h"
#include "model/Mesh.h"

#include <glm/glm.hpp>
#include <string>

class Model {
	private:
		Path filePath;

		std::vector<Mesh*> meshes;

	public:
		Model(const Path &filePath);
		~Model();

		std::string getName() const;
		Path getFilePath() const;

		void addMesh(Mesh* mesh);
		Mesh* getMesh(int index) const;
		std::vector<Mesh*> getMeshes() const;
};
