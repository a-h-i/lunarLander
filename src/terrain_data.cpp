#include "data.hpp"

using namespace graphics;
std::array<graphics::Vertex, data::terrain::verticesCount> data::terrain::vertices = {
    {
        {glm::vec2(-1.0f, 0.0f), tc}, {glm::vec2(-0.5f, 0.0f), tc},
        {glm::vec2(-0.5f, 0.25f), tc}, {glm::vec2(-0.2f, 0.25f), blue},
        {glm::vec2(-0.2f, 0.0f), tc}, {glm::vec2(0.25f, 0.0f), tc},
        {glm::vec2(0.5f, 0.6f), tc}, {glm::vec2(0.75f, 0.0f), tc},
        {glm::vec2(1.0f, 0.0f), tc}

    }};

std::array<GLushort, data::terrain::indiciesCount> data::terrain::indicies = {

    0, 1, 1, 2, 2, 3,
    3, 4, 4, 5, 5, 6,
    6, 7, 7, 8



};