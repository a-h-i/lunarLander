#include "callbacks.hpp"
#include <iostream>


void cbs::glfwError(int errorCode, const char * description) {
    std::cerr << "GLFW Error #" << errorCode << " Description:\n"
              << description << '\n';
}

void cbs::key(GLFWwindow * window, int key, int scancode, int action, int mods) {
    if ( (key == GLFW_KEY_ESCAPE) & (action == GLFW_PRESS) ) {
        glfwSetWindowShouldClose( window, GL_TRUE );
    }
}

void cbs::resize(GLFWwindow * window, const int w, const int h) {
    glViewport( 0, 0, w, h );
}