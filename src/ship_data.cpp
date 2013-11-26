#include "data.hpp"

using namespace graphics;

std::array<graphics::Vertex, data::ship::verticesCount> data::ship::vertices = {
    {
        /*top triangle */
        {glm::vec2(0.0f, 0.5f), white}, {glm::vec2(-0.5f, 0.25f), white},
        {glm::vec2(0.5f, 0.25f), white},
        /* middle box */
        {glm::vec2(-0.5f, -0.25f), white}, {glm::vec2(0.5f, -0.25f), white},
        /*buttom left box*/
        {glm::vec2(-0.35f, -0.25f), white}, {glm::vec2(-0.5f, -0.25f), white},
        {glm::vec2(-0.35f, -0.35f), white}, {glm::vec2(-0.5f, -0.35f), white},
        /* buttom right box */
        {glm::vec2(0.35f, -0.25f), white}, {glm::vec2(0.5f, -0.25f), white},
        {glm::vec2(0.35f, -0.35f), white}, {glm::vec2(0.5f, -0.35f), white}
    }};

std::array<GLushort, data::ship::indiciesCount> data::ship::indicies = {
    
        /* top triangle */
        1, 0, 2,
        /* middle box */
        4, 3, 2, 4, 3, 1,
        /* buttom left box */
        7, 8, 6, 7, 8, 5,
        /* buttom right box */
        11, 12, 10, 11, 12, 9
    };
