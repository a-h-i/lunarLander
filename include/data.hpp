#pragma once
#include "project_headers.hpp"
#include "graphics.hpp"
#include <array>
namespace data {


   
    namespace fuel {
        constexpr std::size_t verticesCount = 16;
        constexpr std::size_t indiciesCount = 24;
        constexpr std::size_t innerLeftFillTopEnd = 10;
        constexpr std::size_t innerLeftFillButtomEnd = 11;
        constexpr std::size_t innerRightFillTopEnd = 14;
        constexpr std::size_t innerRightFillButtomEnd = 15;
        extern std::array<graphics::Vertex, verticesCount> vertices;
        extern std::array<GLushort, indiciesCount> indicies;

        inline void setInnerLeftEnd(graphics::Vertex & top, graphics::Vertex & buttom) {
            vertices[innerLeftFillTopEnd] = top;
            vertices[innerLeftFillButtomEnd] = buttom;
        }

        inline void setInnerRightEnd(graphics::Vertex & top, graphics::Vertex &buttom) {
            vertices[innerRightFillTopEnd] = top;
            vertices[innerRightFillButtomEnd] = buttom;
        }

    }


    namespace ship {
        constexpr std::size_t verticesCount = 13;
        constexpr std::size_t indiciesCount = 21;
        extern std::array<graphics::Vertex, verticesCount> vertices;
        extern std::array<GLushort, indiciesCount> indicies;

    }

    namespace terrain {
        constexpr std::size_t verticesCount = 9;
        constexpr std::size_t indiciesCount = 16;
        extern std::array<graphics::Vertex, verticesCount> vertices;
        extern std::array<GLushort, indiciesCount> indicies;
    }


    constexpr std::size_t totalVertices = fuel::verticesCount + ship::verticesCount + terrain::verticesCount;
    constexpr std::size_t totalIndicies = fuel::indiciesCount + ship::indiciesCount + terrain::indiciesCount;
}