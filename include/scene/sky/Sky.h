#pragma once

#include "model/Model.h"
#include "shader/ShaderProgram.h"
#include "scene/structure/Object.h"

struct SkyBoxImages {
	Path front;
	Path back;
	Path left;
	Path right;
	Path top;
	Path bottom;
};

class SkyBox;
class SkyDome;
class Sky : public Object {
	protected:
		Model* model;
		ShaderProgram* shaderProgram;

		GLuint texture;

	public:
		Sky(const std::string &name);
		virtual ~Sky() = default;

		static Sky* createSkyBox(const std::string &name, SkyBoxImages* images);
		static Sky* createSkyBox(const std::string &name, Path* folderPath);
		static Sky* createSkyDome(const std::string &name, Path* image);
		static Sky* createSkySphere(const std::string &name, Path* image);

		virtual void init() = 0;
		virtual void draw() = 0;
};