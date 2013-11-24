#pragma once

//#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "exceptions.hpp"


enum class ShaderType  : GLenum {VertexShader = GL_VERTEX_SHADER, FragmentShader = GL_FRAGMENT_SHADER};
    inline std::string toString(const ShaderType e) {
    switch (e) {
        case ShaderType::VertexShader:
            return "VertexShader";
        case ShaderType::FragmentShader:
            return "FragmentShader";
        default:
            return "Unknown Type";
    }

}

extern int windowWidth;
extern int windowHeight;


