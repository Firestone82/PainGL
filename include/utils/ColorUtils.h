#pragma once

#include <glm/glm.hpp>
#include <iostream>

glm::vec3 nextRainbowColor(const glm::vec3 &currentColor) {
	float r = currentColor[0];
	float g = currentColor[1];
	float b = currentColor[2];

	// Linear from red to green to blue then back
	if (r >= 1.0f && g < 1.0f && b <= 0.0f) {
		g += 0.01f;
	} else if (r > 0.0f && g >= 1.0f && b <= 0.0f) {
		r -= 0.01f;
	} else if (r <= 0.0f && g >= 1.0f && b < 1.0f) {
		b += 0.01f;
	} else if (r <= 0.0f && g > 0.0f && b >= 1.0f) {
		g -= 0.01f;
	} else if (r < 1.0f && g <= 0.0f && b >= 1.0f) {
		r += 0.01f;
	} else if (r >= 1.0f && g <= 0.0f && b > 0.0f) {
		b -= 0.01f;
	}

	return glm::vec3(r, g, b);
}