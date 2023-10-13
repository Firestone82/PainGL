#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace Transform {
    enum Type {
        COMPOSITE,
        TRANSLATE,
        ROTATE,
        SCALE
    };

    class Component {
        protected:
            glm::mat4 matrix = glm::mat4(1.0f);
            Transform::Type type;

        public:
            explicit Component(Transform::Type type) : type(type) {}
            virtual glm::mat4 resultMatrix() const = 0;
			virtual ~Component() = default;

            virtual void calculate() = 0;
            Transform::Type getType() const;
    };


    class Rotation : public Component {
        private:
            glm::vec3 rotationVector;
            void calculate() override;

        public:
            /* -- */ Rotation(float x, float y, float z);
            explicit Rotation(glm::vec3 rotationVector);
			/* - */ ~Rotation() override = default;

            glm::vec3 getVector();
            glm::mat4 resultMatrix() const override;
    };

    class Translate : public Component {
        protected:
            glm::vec3 translationVector;

        private:
            void calculate();

        public:
            /* -- */ Translate(float x, float y, float z);
            explicit Translate(glm::vec3 translationVector);
			/* - */ ~Translate() override = default;

            glm::vec3 getVector();
            glm::mat4 resultMatrix() const override;
    };

    class Scale : public Component {
        private:
            glm::vec3 scaleVector;
            void calculate() override;

        public:
            explicit Scale(float scale);
            explicit Scale(glm::vec3 scaleVector);
            /* -- */ Scale(float x, float y, float z);
			/* - */ ~Scale() override = default;

            glm::vec3 getVector();
            glm::mat4 resultMatrix() const override;
    };

    class Composite : public Component {
        private:
            std::vector<Component*> transforms;
            void calculate() override;

	    public:
            explicit Composite(const std::vector<Component*> &transforms);
	        /* - */ ~Composite() override;

            std::vector<Component*>& get();
            glm::mat4 resultMatrix() const override;

            bool isEmpty();

    };
};

class Transformation {
    private:
        Transform::Composite* transform = new Transform::Composite({});

    public:
        /* -- */ Transformation();
        explicit Transformation(Transform::Composite* composite);
		/* - */ ~Transformation();

        void setTransformation(Transform::Composite* composite);
        Transform::Composite* get();

        glm::mat4 resultMatrix();
};