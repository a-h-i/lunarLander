#include "game.hpp"


Game::Game(graphics::Graphics * g): g(g), units(2) {
    // reference time
    start = std::chrono::system_clock::now();
}


void Game::render() {

    if(!isGameover()) {

        // get current time
        auto now = std::chrono::system_clock::now();
        auto ticks = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() / 250;
        if(ticks > units) {
            units+= 2; // each time unit is 500 ms which corresponds to 1% fuel usage
            fuel.clockTick();
        }
        // constant projection matrix
        static glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
        // note : Fuel tank and Terrain model matricies are constant
        // fuel tank rendering        
        // take fuel to upper left corner
        static glm::mat4 fuelScale = glm::scale(glm::mat4(), glm::vec3( 0.2f, 0.2f, 1.0f));
        static glm::mat4 fuelTranslate = glm::translate(glm::mat4(), glm::vec3(-0.82f, 0.9f, 0.0f));
        static glm::mat4 fuelMVP = projection * fuelTranslate *  fuelScale;
        fuel.render(g, fuelMVP);
        // terrain rendering
        // take terrain to buttom side
        static glm::mat4 terrainTranslation =  glm::translate(glm::mat4(), glm::vec3(0.0f, -1.0f, 0.0f));
        static glm::mat4 terrainMVP = projection * terrainTranslation;
        terrain.render(g, terrainMVP);

        //ship rendering
        // ship scale matrix is static
        static glm::mat4 shipScale = glm::scale(glm::mat4(), glm::vec3(0.1f, 0.1f, 1.0f));
        glm::mat4 shipMVP = projection * shipScale;
        ship.render(g, shipMVP);
    }
}

bool Game::isGameover() {

    bool fuelEmpty = fuel.isEmpty();
    return (fuelEmpty);
}

void Game::reset() {
    fuel.reset();
}

void Game::moveLeft(){

}
void Game::moveRight() {

}
void Game::moveUp() {

}
void Game::moveDown(){

}