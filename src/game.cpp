#include "game.hpp"
#include "utility.hpp"
#include <iostream>

constexpr float shipScaleY = 0.1f;
constexpr float shipScaleX = 0.1f;
constexpr float shipHeight = 0.85;
constexpr float shipWidth = 1.0f;
 

Game::Game(graphics::Graphics * g): g(g), units(2), won(false) {
    // reference time
    start = std::chrono::system_clock::now();
}

inline void checkScreenBoundries(glm::vec3 &pos){
    pos.x = utility::math::clamp(pos.x, 1.0f - (shipWidth / 2.0f) * shipScaleX, -1.0f - (shipWidth / 2.0f) * shipScaleX);
    pos.y = utility::math::clamp(pos.y, 1.0f - (shipHeight / 2.0f) * shipScaleY
                                , -1.0f - (shipHeight / 2.0f) * shipScaleY );
}



void Game::render() {



    

        // get current time
        auto now = std::chrono::system_clock::now();
        auto ticks = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() / 250;
        if(ticks > units && !isGameover()) {
            units+= 2; 
            // each time unit is 500 ms which corresponds to 1% fuel usage
            fuel.clockTick();
            // apply gravity each timeUnit
            static glm::vec3 grav(0.0f, -0.02f, 0.0f);
            ship.pos += grav;
            checkScreenBoundries(ship.pos);
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
        static glm::mat4 shipScale = glm::scale(glm::mat4(), glm::vec3(shipScaleX, shipScaleY, 1.0f));
        // move to position 
        // Ship originaly centered at origin (model space)
        glm::mat4 shipTranslate = glm::translate(glm::mat4(), ship.pos);
        glm::mat4 shipMVP = projection * shipTranslate * shipScale;
        ship.render(g, shipMVP);
    
}

bool Game::terrainCollideHelper() {

     float currentButtom = ship.pos.y - (shipHeight / 2.0f) * shipScaleY;
     float currentRight =  ship.pos.x + (shipWidth / 2.0f) * shipScaleX;
     float currentLeft =  ship.pos.x - (shipWidth / 2.0f) * shipScaleX;

     constexpr float leftLineSlope = ((-0.4f) - (-1.0f) ) / ( 0.5f - 0.25f );
     constexpr float rightLineSlope = ((-1.0f) - (-0.4f)) / (0.75f - 0.5f);
     constexpr float leftIntercept = -1.6f;
     constexpr  float rightIntercept = 0.8f;

     if(currentButtom <= -1.0f) {
        return true;
    }

    // on pad
    if( (currentButtom <= -0.75f) & (currentRight <= -0.21f ) & (currentLeft >= -0.51f) ) {
        if(!won) {
            std::cout << "Congratulations Pilot !\n";
        }
        won = true;        
        return true;
    }

    //collided with rect
    if ( (currentButtom < -0.75f) & (currentLeft <= -0.2f) & (currentRight >= -0.5f) ) {
        return true;
    }
    // collided with triangle
    if(currentButtom <= -0.4f) {
        if((currentButtom <= (leftLineSlope * currentRight + leftIntercept) ) && currentRight >= 0.25f && currentRight <=0.5f ) {
            return true;
        }

        if ( ( currentButtom <= rightLineSlope * currentLeft + rightIntercept ) && currentLeft <= 0.75f && currentLeft >= 0.5f  ){
            return true;
        }
    }


    
    return false;
}

bool Game::isGameover() {

    bool fuelEmpty = fuel.isEmpty();
    //buttom of ship area box
    bool collide = terrainCollideHelper();
    return fuelEmpty | collide;
}

void Game::reset() {
    fuel.reset();
    ship.pos.x = ship.pos.y = 0.0f;

}

constexpr float deltaMove = 0.05f;

void Game::moveLeft(){
    if(!isGameover()) {
        static glm::vec3 pulse(-deltaMove, 0.0f, 0.0f);
        auto const shipPos = ship.pos;
        ship.pos = shipPos + pulse; // translate
        
      if(ship.pos.x <= (-1.0f - (shipWidth / 2.0f) * shipScaleX ) )  {
            // screen boundry
            ship.pos.x = -1.0f;
        }
        
    }
}
void Game::moveRight() {
    if(!isGameover()) {
        static glm::vec3 pulse(deltaMove, 0.0f, 0.0f);
        auto const shipPos = ship.pos;
        ship.pos = shipPos + pulse; // translate
        
       if(ship.pos.x >= (1.0f - (shipWidth / 2.0f) * shipScaleX) ) {
            // screen boundry
            ship.pos.x = 1.0f;
        }
        
    }
}
void Game::moveUp() {

    if(!isGameover()) {
        static glm::vec3 pulse(0.0f, deltaMove, 0.0f);
        auto const shipPos = ship.pos;
        ship.pos = shipPos + pulse; // translate
        if(ship.pos.y >= (1.0f - (shipHeight / 2.0f) * shipScaleY ) )  {
            // screen boundry
            ship.pos.y = 1.0f;
        }
        

    }
}
void Game::moveDown(){

    if(!isGameover()) {
        static glm::vec3 pulse(0.0f, -deltaMove, 0.0f);
        auto const shipPos = ship.pos;
        ship.pos = shipPos + pulse; // translate
        if(ship.pos.y <= -1.0f) {
            // screen boundry
            ship.pos.y = shipPos.y;
        }
        
    }
}