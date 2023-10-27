#pragma once

#include "event/structure/Event.h"

class Light;

class LightUpdateEvent : public Event {
	private:
		Light* light;

	public:
		explicit LightUpdateEvent(Light* light)
			: Event(EventType::LIGHT_UPDATE), light(light) {}

		Light* getLight() const {
			return light;
		}
};