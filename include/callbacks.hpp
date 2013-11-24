#pragma once
#include "project_headers.hpp"

namespace cbs {
    /**
     * @brief GLFW Error Callback.
     */
    void glfwError(int errorCode, const char * description);
    /**
     * @brief Window key callback.
     */
    void key(GLFWwindow * window, int key, int scancode, int action, int mods);
    /**
     * @brief Frame buffer resize callback.
     */ 
    void resize(GLFWwindow * window, const int w, const int h);
}