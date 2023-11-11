#pragma once

#include <string>

class Object {
	protected:
		int id = -1;
		std::string name;

	public:
		explicit Object(const std::string &name) {
			this->name = name;
		}

		virtual ~Object() = default;

		void setID(int id) {
			this->id = id;
		}

		int getID() {
			return this->id;
		}

		std::string getName() {
			return this->name;
		}
};