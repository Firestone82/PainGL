#pragma once

#include "scene/structure/Randerable.h"
#include "texture/Image.h"
#include "model/Model.h"
#include "shader/ShaderProgram.h"
#include "scene/structure/Object.h"

#include <string>
#include <GL/gl.h>

class SkyBox : public Object {
	private:
		Model* model;
		ShaderProgram* shaderProgram;

		GLuint texture;

	public:
		SkyBox(const std::string &name, std::vector<Path> images);
		~SkyBox();

		void draw();
};