#version 330 core
layout (location = 0) in vec2 inVert;
layout (location = 1) in vec4 inColor;
uniform mat4 mvp;
smooth out vec4 color;

void main() {
    vec4 homoVect = vec4(inVert, 0.0f, 1.0f);
    gl_Position = mvp * homoVect;
    color = inColor;
}