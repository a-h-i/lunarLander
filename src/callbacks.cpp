#include "callbacks.hpp"
#include "game.hpp"
#include <iostream>


void cbs::glfwError(int errorCode, const char * description) {
    std::cerr << "GLFW Error #" << errorCode << " Description:\n"
              << description << '\n';
}

void cbs::key(GLFWwindow * window, int key, int scancode, int action, int mods) {
    if ( (key == GLFW_KEY_ESCAPE) & (action == GLFW_PRESS) ) {
        // close window
        glfwSetWindowShouldClose( window, GL_TRUE );
    }else if( (key == GLFW_KEY_RIGHT) & ( (action == GLFW_PRESS) | (action == GLFW_REPEAT) ) ) {
        gamePtr->moveRight();
    }else if( (key == GLFW_KEY_LEFT) & ( (action == GLFW_PRESS) | (action == GLFW_REPEAT) ) ) {
        gamePtr->moveLeft();
    }else if( (key == GLFW_KEY_DOWN) & ( (action == GLFW_PRESS) | (action == GLFW_REPEAT) ) ) {
        gamePtr->moveDown();
    }else if( (key == GLFW_KEY_UP) & ( (action == GLFW_PRESS) | (action == GLFW_REPEAT) ) ) {
        gamePtr->moveUp();
    }else if( (key == GLFW_KEY_ENTER) & (action == GLFW_PRESS) ) {
        //restart game
        gamePtr->reset();
    }

}

void cbs::resize(GLFWwindow * window, const int w, const int h) {
    glViewport( 0, 0, w, h );
}