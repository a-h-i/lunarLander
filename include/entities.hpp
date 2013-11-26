#pragma once
#include "project_headers.hpp"
#include "graphics.hpp"
#include "utility.hpp"
#include <functional>

namespace component {



    struct Percent {
    private:
        float value;
        std::function<float(float)> func = std::bind(utility::math::clamp, std::placeholders::_1, 1.0f, 0.0f);
    public:
        Percent(float init = 1.0f): value(init){}
        explicit operator float() {
            return value;
        }
        Percent & operator+(const Percent &other) {
            value = func(value + other.value);
            return *this;
        }
        Percent & operator-(const Percent &other) {
            value = func(value - other.value);
            return *this;
        }
        Percent & operator+(float other) {
            value = func(value + other);
            return *this;
        }
        Percent & operator-(float other) {
            value = func(value - other);
            return *this;
        }
    };
}

namespace entities {



    class Terrain{
    GLuint shader;
    GLint matLocation;

    public:
        Terrain();
        void render(graphics::Graphics *g, glm::mat4 &mvp);
        ~Terrain();
    };

    class Ship {
        GLuint shader;
        GLint matLocation;
    public:
        Ship();
        void render(graphics::Graphics *g, glm::mat4 &mvp);
        ~Ship();
        glm::vec3 pos;

    };
    class Fuel {
        GLuint shader;
        GLint matLocation;
        component::Percent p, prevP;
    public:
        Fuel();
        void render(graphics::Graphics *g, glm::mat4 &mvp);
        void clockTick();
        bool isEmpty() { return static_cast<float>(p) <= 0.0f;}
        void reset();
        ~Fuel();
    };
}