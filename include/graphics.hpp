#pragma once
#include "project_headers.hpp"
#include <cstddef>
#include <string>
#include <vector>

namespace graphics {
extern const std::string GENERIC_VSHADER_PATH;
extern const std::string GENERIC_FSHADER_PATH;
extern const std::string GENEREIC_SHADER_MAT;

typedef glm::vec3 rgb;
/**
 * @brief Vertex.
 * @details uniform vertex for all models
 * 
 */
struct Vertex {
    GLfloat x, y, r, g, b, extra;
    Vertex(const glm::vec2 pos, const rgb color, const GLfloat extra = 1.0f ):
            x(pos.x), y(pos.y), r(color.x), g(color.y), b(color.z), extra(extra){}

    static constexpr GLenum type() {return GL_FLOAT;}
    static constexpr std::size_t posStride() {return sizeof(Vertex);}
    static constexpr void * posOffset() {return (void *)0;}
    static constexpr std::size_t posSize() {return 2;}
   
    static constexpr std::size_t colorStride() { return sizeof(Vertex);}
    static constexpr void * colorOffset() { return (void *) (2 * sizeof(GLfloat));}
    static constexpr std::size_t colorSize() {return 3;}

    static constexpr std::size_t extraStride() { return sizeof(Vertex);}
    static constexpr void * extraOffset() {  return (void *) ( 4 * sizeof(GLfloat));}
    static constexpr std::size_t extraSize() { return 1;}
}  __attribute__((__packed__)); // no padding

const rgb white(1.0f, 1.0f, 1.0f);
const rgb black(0.0f, 0.0f, 0.0f);
const rgb red(1.0f, 0.0f, 0.0f );
const rgb blue(0.0f, 0.0f, 1.0f);
const rgb green(0.0f, 1.0f, 0.0f);
const rgb tc(white);

class Graphics {
    GLuint vao, vbos[2];
public:
    Graphics();
    void updateShipModel();
    void updateFuelModel();
    void updateTerrainModel();
    void drawFuel();
    void drawShip();
    void drawTerrain();
    ~Graphics();
};

}