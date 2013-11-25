#version 330 core
layout (location = 3) in vec2 pos;

uniform mat4 mvp;


void main() {
    vec4 homoVert = vec4(pos, 0.0f, 1.0f);
    gl_Position = mvp * homoVert;
    //gl_Position = homoVert;
    

}