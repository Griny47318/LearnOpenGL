#version 460 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
out vec3 vertexColor;
uniform float temp;
void main(){
gl_Position = vec4(position.x + temp, position.y, position.z, 1.0);
vertexColor = color;
}