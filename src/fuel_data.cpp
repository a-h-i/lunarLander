#include "data.hpp"

using namespace graphics;

std::array<Vertex, data::fuel::verticesCount> data::fuel::vertices = {
    { /*outer shell*/
      /* left box */
       {glm::vec2(-0.5f, -0.25f), red}, {glm::vec2(-0.5f, 0.25f), red},
       {glm::vec2(0.5f, 0.25f), red}, {glm::vec2(0.5f, -0.25f), red},
      /* right box */  
       {glm::vec2(0.5f, -0.05f), red} , {glm::vec2(0.5f, 0.05f), red},
       {glm::vec2(0.6f, 0.05f), red}, {glm::vec2(0.6f, -0.05f), red},
       /* inner fill */
       /*left box */
       {glm::vec2(-0.5f, -0.25f), blue}, {glm::vec2(-0.5f, 0.25f), blue},
       /*end top*/                      /*end buttom */
       {glm::vec2(0.5f, 0.25f), blue}, {glm::vec2(0.5f, -0.25f), blue},
       /*right box */
       {glm::vec2(0.5f, -0.05f), blue}, {glm::vec2(0.5f, 0.05f), blue},
       /*end top */                        /*end buttom*/
       {glm::vec2(0.6f, 0.05f), blue}, {glm::vec2(0.6f, -0.05f), blue}
    }};
std::array<GLushort, data::fuel::indiciesCount> data::fuel::indicies = {
    /*inner fill */
    /*left box*/
    8, 9, 10, 8, 10, 11,
    /*right box */
    12, 13, 14, 12, 14, 15,
    /*outer shell */
    /*left box */
    0, 1, 2, 0, 2, 3
    /* right box */
    4, 5, 6, 4, 6, 7
}