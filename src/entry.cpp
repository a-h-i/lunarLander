#include "project_headers.hpp"
#include "callbacks.hpp"
#include "ui.hpp"

#include <boost/scope_exit.hpp>
#include <iostream>
#include <cstdlib>



int main() {
    glfwSetErrorCallback(cbs::glfwError);
    if(!glfwInit()) {
        std::cerr << "Could not init glfw\n";
        return EXIT_FAILURE;
    }
    BOOST_SCOPE_EXIT(void) {
        glfwTerminate();
    }BOOST_SCOPE_EXIT_END

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    windowWidth = 400;
    windowHeight = 400;
    GLFWwindow * window = glfwCreateWindow(windowWidth, windowHeight, "Lunar Lander", nullptr, nullptr );
    if(window == nullptr) {
        std::cerr << "Coult not create Window\n";
        return EXIT_FAILURE;
    }
    BOOST_SCOPE_EXIT(window) {
        glfwDestroyWindow(window);
    }BOOST_SCOPE_EXIT_END
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    GLenum glewStatus = glewInit();
    if(glewStatus != GLEW_OK) {
        std::cerr << "Failed to initalize glew log :\n" << glewGetErrorString(glewStatus) << '\n';
        return EXIT_FAILURE;
    }    

    glfwSetFramebufferSizeCallback(window, cbs::resize);
    glfwSetKeyCallback(window, cbs::key);
    cbs::resize(window, windowHeight, windowWidth);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(0.0f);

    ui::FuelControl fc(-0.5);
    ui::FuelView fv(fc);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // draw ui
        fv.draw();
        glfwSwapBuffers(window);
    }

    return EXIT_SUCCESS;
}