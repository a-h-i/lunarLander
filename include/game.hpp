#pragma once
#include "project_headers.hpp"
#include "graphics.hpp"
#include "entities.hpp"

#include <chrono>

class Game {
    graphics::Graphics * g;
    entities::Terrain terrain;
    entities::Fuel fuel;
    entities::Ship ship;
    std::chrono::time_point<std::chrono::system_clock> start;
    long long  units;
    bool won;
    bool isGameover();
    bool terrainCollideHelper();
public:
    Game(graphics::Graphics * g);
    void render();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void reset();

    
};

extern Game * gamePtr;