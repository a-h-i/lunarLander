#pragma once
#include "project_headers.hpp"
#include <algorithm>
#include <fstream>
#include <string>
#include <memory>





namespace utility{



/**
 *@brief returns a string containing the entire file.
 *@detail File must be an ASCII text file.
 */
inline std::string readFile(std::ifstream &file) {
    std::string toReturn;
    for(std::string line; std::getline(file, line); )
    {
        toReturn += line + "\n";
    }
    return toReturn;
}


/**
 * @brief compiles a shader from source.
 * @exception ShaderCompilationError if failed to compile source.
 */
inline GLuint createShader(const std::string &source, ShaderType type) {
    GLuint shader = glCreateShader(static_cast<GLenum>(type));
    const char * src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if(status == GL_FALSE) {
        // error while compiling
        GLint infoLogSize;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogSize);
        std::unique_ptr<char> strInfoLog(new char[infoLogSize + 1]);
        glGetShaderInfoLog(shader, infoLogSize, nullptr, strInfoLog.get());
        throw ShaderCompilationError(std::string("Shader Type : ") + toString(type) + " Info:\n" + strInfoLog.get());
    }
    return shader;
}


/**
 *@brief creates a pogram from a container of shaders.
 *@exception ShaderLinkingException if linking fails.
 */
template <typename Container>
GLuint createProgram(Container&& shaders) {
    GLuint prog = glCreateProgram();

    for(auto &i : shaders) {
        glAttachShader(prog, i);
    }
    glLinkProgram(prog);
    GLint status;
    // get link status
    glGetProgramiv(prog, GL_LINK_STATUS, &status);

    if(status == GL_FALSE) {
        // error while linking
        GLint infoLogSize;
        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &infoLogSize);
        std::unique_ptr<char> strInfoLog(new char[infoLogSize + 1]);
        glGetProgramInfoLog(prog, infoLogSize, nullptr, strInfoLog.get());            
        throw ShaderLinkingError(std::string("Info:\n") + std::string(strInfoLog.get()));
    }

    for(auto &i : shaders) {
        glDetachShader(prog, i);
    }
    return prog;
}


/**
 * @brief creates a shader Program containing a fragment and vertex shader.
 * 
 * @param vShaderPath path to vertex shader source file.
 * @param fShaderPath path to fragment shader source file.
 * @exception ShaderLoadError if failed to open files.
 * @exception ShaderLinkingError if failed to link program.
 * @exception ShaderCompilationError if failed to compile shaders.
 * @return program ID
 */
inline GLuint loadShader(const std::string &vShaderPath, const std::string &fShaderPath) {
    std::ifstream vShader(vShaderPath);
    std::ifstream fShader(fShaderPath);

    if(vShader.good() && fShader.good()) {
        std::array<GLuint, 2> shaders;
        shaders[0] = utility::createShader( utility::readFile(vShader), ShaderType::VertexShader );
        shaders[1] = utility::createShader( utility::readFile(fShader), ShaderType::FragmentShader );
        auto prog =  utility::createProgram(shaders);
        std::for_each(std::begin(shaders), std::end(shaders), glDeleteShader);
        return prog;

    }else {
        throw ShaderLoadError("Could not open UI shader files");
    }
}




namespace math {

    inline float clamp(const float src, float max, float min ) {

    return src < min ? min : (src > max ? max : src);
    }

} // namespace utility::math


} // namsepsace utility