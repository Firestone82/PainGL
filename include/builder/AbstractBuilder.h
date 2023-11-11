#pragma once

template <typename T>
class AbstractBuilder {
	protected:
		T* object;

	public:
		AbstractBuilder() = default;

		virtual T* build() {
			return object;
		}
};