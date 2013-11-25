#include "data.hpp"

std::array<glm::vec2, data::fuel_outer_size> data::fuel_tank_outer = {
    {
        glm::vec2(-0.5f, 0.25f) ,  glm::vec2(0.5f, 0.25f),
        glm::vec2(0.5f, 0.05f), glm::vec2(0.6f, 0.05f),
        glm::vec2(0.6f, -0.05f),  glm::vec2(0.5f, -0.05f),
        glm::vec2(0.5f, -0.25f), glm::vec2(-0.5f, -0.25f)
    }};


std::array<glm::vec2, data::lander_model_size > data::lander_model = {
    { 
       glm::vec2(0.5f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(0.5f, 1.0f)
    }};
std::array<GLushort, data::lander_indices_size> data::lander_indices = 
    {
      0, 1, 1, 2
    };

int windowHeight = 0;
int windowWidth = 0;