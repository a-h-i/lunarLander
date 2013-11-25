#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in float extra;

smooth out vec4 oColor;
flat out float vExtra
uniform mat4 mvp

void main() {
    vec4 homoPos = vec4(pos, 0.0f, 1.0f);
    vExtra = extra;
    gl_Position = mvp * homoPos;
    oColor = vec4(color, 1.0f);
}