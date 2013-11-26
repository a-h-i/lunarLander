#include "entities.hpp"
#include "utility.hpp"


entities::Terrain::Terrain() : shader(utility::loadShader(graphics::GENERIC_VSHADER_PATH,
                                 graphics::GENERIC_FSHADER_PATH)),
                                 matLocation(glGetUniformLocation(shader, 
                                    graphics::GENEREIC_SHADER_MAT.c_str())) {}

void entities::Terrain::render(graphics::Graphics *g, glm::mat4 &mvp) {
    glUseProgram(shader);
    glUniformMatrix4fv(matLocation, 1, GL_FALSE, &mvp[0][0]);
    g->drawTerrain();
    glUseProgram(0);
}

entities::Terrain::~Terrain() {
    glDeleteProgram(shader);
}