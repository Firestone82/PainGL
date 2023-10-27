#include "Engine.h"
#include "utils/Logger.h"
#include "scene/entity/EntityHandler.h"
#include "event/type/CameraEvents.h"

EntityHandler::~EntityHandler() {
	for (const auto &entity: this->entities) {
		delete entity;
	}
}

void EntityHandler::addEntity(Entity* entity) {
	entity->setID(this->entities.size());
	this->entities.push_back(entity);
}

void EntityHandler::removeEntity(Entity* entity) {
	this->entities.erase(std::remove(this->entities.begin(), this->entities.end(), entity), this->entities.end());

	// Reorder IDs of entities
	for (int i = 0; i < this->entities.size(); i++) {
		this->entities[i]->setID(i);
	}
}

const std::vector<Entity*>& EntityHandler::getEntities() const {
	return this->entities;
}