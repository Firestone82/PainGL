#pragma once

#include "event/structure/Event.h"

class AbstractLight;

class LightUpdateEvent : public Event {
	private:
		AbstractLight* light;

	public:
		explicit LightUpdateEvent(AbstractLight* light)
			: Event(EventType::LIGHT_UPDATE), light(light) {}

		AbstractLight* getLight() const {
			return light;
		}
};