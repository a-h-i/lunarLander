#include "entities.hpp"
#include "utility.hpp"


entities::Ship::Ship() : shader(utility::loadShader(graphics::GENERIC_VSHADER_PATH,
                                 graphics::GENERIC_FSHADER_PATH)),
                                 matLocation(glGetUniformLocation(shader, 
                                    graphics::GENEREIC_SHADER_MAT.c_str())), pos(0.0f, 0.0f, 0.0f) {}

void entities::Ship::render(graphics::Graphics *g, glm::mat4 &mvp) {
    glUseProgram(shader);
    glUniformMatrix4fv(matLocation, 1, GL_FALSE, &mvp[0][0]);
    g->drawShip();
    glUseProgram(0);
}

entities::Ship::~Ship() {
    glDeleteProgram(shader);
}