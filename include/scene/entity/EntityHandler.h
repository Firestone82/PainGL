#pragma once

#include "scene/entity/Entity.h"

class EntityHandler {
	private:
		std::vector<Entity*> entities;

	public:
		~EntityHandler();

		void addEntity(Entity* entity);
		void removeEntity(Entity* entity);

		const std::vector<Entity*>& getEntities() const;
};