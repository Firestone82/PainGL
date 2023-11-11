#include "scene/sky/Sky.h"

#include "scene/sky/skybox/SkyBox.h"
#include "scene/sky/skydome/SkyDome.h"

Sky::Sky(const std::string &name) : Object(name) {
	// Empty
}

Sky* Sky::createSkyBox(const std::string &name, SkyBoxImages images) {
	return new SkyBox(name, images);
}

Sky* Sky::createSkyBox(const std::string &name, Path folderPath) {
	SkyBoxImages images = {
		folderPath.toString() + "front.jpg",
		folderPath.toString() + "back.jpg",
		folderPath.toString() + "left.jpg",
		folderPath.toString() + "right.jpg",
		folderPath.toString() + "top.jpg",
		folderPath.toString() + "bottom.jpg",
	};

	return new SkyBox(name, images);
}

Sky* Sky::createSkyDome(const std::string &name, Path image) {
	return new SkyDome(name, image);
}