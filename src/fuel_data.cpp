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
    11, 8, 9, 9, 10, 11,
    /*right box */
    15, 12, 13, 13, 14, 15, 
    /*outer shell */
    0, 1, 2, 5, 6, 7, 4, 3
  };