#version 330 core
smooth in vec4 oColor;
flat in float vExtra;
out vec4 outColor;

void main() {
    
    if(vExtra == 10.0f) {
        outColor = vec4(0.0f, 0.0f, 0.0f);
    }else {
        outColor = oColor;
    }
}