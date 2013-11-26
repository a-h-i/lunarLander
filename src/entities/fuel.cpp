#include "entities.hpp"
#include "data.hpp"
#include "utility.hpp"


entities::Fuel::Fuel() : shader(utility::loadShader(graphics::GENERIC_VSHADER_PATH,
                                 graphics::GENERIC_FSHADER_PATH)),
                                 matLocation(glGetUniformLocation(shader, 
                                    graphics::GENEREIC_SHADER_MAT.c_str())), p(1.0f), prevP(1.0f) {}

void entities::Fuel::render(graphics::Graphics *g, glm::mat4 &mvp) {
    glUseProgram(shader);
    glUniformMatrix4fv(matLocation, 1, GL_FALSE, &mvp[0][0]);
    // calculate fill percentage / area


    if(static_cast<float>(p) != static_cast<float>(prevP)) {
        // calculations for bottle body (minus cap)
        static constexpr float LEFT_PERCENT = 0.9f; // body is 9 % of tank
        static constexpr float RIGHT_PERCENT = 0.1f; // bottle is 10% of tank
        // endpoint for body
        const float leftX = -0.5f  + utility::math::clamp(static_cast<float>(p) / LEFT_PERCENT, 1.0f, 0.0f);
        data::fuel::setInnerLeftEnd(graphics::Vertex(glm::vec2(leftX, 0.25f), graphics::blue), graphics::Vertex(glm::vec2(leftX, -0.25f), graphics::blue));
        // calculation for bottle cap
        if(static_cast<float>(p) >= LEFT_PERCENT) {
            const float percent = 1.0f - ((1.0f - static_cast<float>(p)) * (RIGHT_PERCENT * 100.0f));
            const float deltaX = (0.6f - 0.5f ) * percent;
            const float minX = 0.5f;
            // end point for cap
            const float maxX = minX + deltaX;
            const float topY = 0.05f;
            const float buttomY = -0.05f;            
            data::fuel::setInnerRightEnd(graphics::Vertex(glm::vec2(maxX, topY), graphics::blue), graphics::Vertex(glm::vec2(maxX, buttomY), graphics::blue));
        }
        prevP = p;
        g->updateFuelModel();
    }
    g->drawFuel();
    glUseProgram(0);
}


void entities::Fuel::clockTick() {
    p = p - 0.01f; // use 1% fuel
}

entities::Fuel::~Fuel() {
    glDeleteProgram(shader);
}

void entities::Fuel::reset() {
    p = component::Percent(1.0f);

}