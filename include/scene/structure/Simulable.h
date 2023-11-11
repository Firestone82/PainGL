#pragma once

#include <functional>

template<typename T>
class Simulable {
	protected:
		std::function<void(T*, double)> simulateFunction;

	public:
		Simulable() = default;
		virtual ~Simulable() = default;

		virtual void simulate(double deltaTime) {
			if (this->simulateFunction != nullptr) {
				this->simulateFunction(static_cast<T*>(this), deltaTime);
			}
		}
};