#version 330 core

smooth in vec4 color;
out vec4 outColor;

void main() {
   if(color.z != 0.0f) {
    outColor.y = mix(color.y, 0.02f, abs(gl_FragCoord.x/2));
   }
   outColor.xzw = color.xzw; 
}