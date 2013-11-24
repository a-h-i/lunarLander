#pragma once
#include <stdexcept>





struct ShaderError : std::runtime_error {
    ShaderError(std::string what) : runtime_error(what) {}
};

struct ShaderLoadError : ShaderError {
    ShaderLoadError(std::string what) : ShaderError(what) {}
};
struct ShaderCompilationError : ShaderError{
    ShaderCompilationError(std::string what): ShaderError(what) {}
};

struct ShaderLinkingError : ShaderError {
    ShaderLinkingError(std::string what): ShaderError(what) {}
};

