#pragma once
#include "project_headers.hpp"
#include <cstddef>
#include <vector>

namespace graphics {

typedef glm::vec3 rgb;
/**
 * @brief Vertex.
 * @details uniform vertex for all models
 * 
 */
struct Vertex {
    float x, y, r, g, b, extra;
    Vertex(const glm::vec2 & pos, const rgb & color, const float extra = 0.0f ):
            x(pos.x), y(pos.y), r(color.x) g(color.y), b(color.z), extra(extra){}

    static constexpr GLenum type() {return GL_FLOAT;}
    static constexpr std::size_t posStride() {return 4 * sizeof(float);}
    static constexpr std::size_t posOffset() {return 0;}
    static constexpr std::size_t posSize() {return 2;}
   
    static constexpr std::size_t colorStride() { return 3 * sizeof(float);}
    static constexpr std::size_t colorOffset() { return posSize() * sizeof(float);}
    static constexpr std::size_t colorSize() {return 3;}

    static constexpr std::size_t extraStride() { return 5 * sizeof(float);}
    static constexpr std::size_t extraOffset() { return 5 * sizeof(float);}
    static constexpr std::size_t extraSize() { return 1;}
};

const rgb white(1.0f, 1.0f, 1.0f);
const rgb black(0.0f, 0.0f, 0.0f);
const rgb red(1.0f, 0.0f, 0.0f );
const rgb blue(0.0f, 0.0f, 1.0f);
const rgb green(0.0f, 1.0f, 0.0f);

class Graphics {
    GLuint vao, vbos[2];
    Graphic();
    void updateShipModel(Vertex *);
    void updateFuelModel(Vertex *);
    void updateTerrainModel(Vertex *);
    void drawFuel();
    void drawShip();
    void drawTerrain();
    ~Graphics();
};

}