#include "data.hpp"
 std::array<glm::vec2, data::fuel_outer_size> data::fuel_tank_outer = {
    {
        glm::vec2(-0.5f, 0.25f) ,  glm::vec2(0.5f, 0.25f),
        glm::vec2(0.5f, 0.05f), glm::vec2(0.6f, 0.05f),
        glm::vec2(0.6f, -0.05f),  glm::vec2(0.5f, -0.05f),
        glm::vec2(0.5f, -0.25f), glm::vec2(-0.5f, -0.25f)
    }};

int windowHeight = 0;
int windowWidth = 0;