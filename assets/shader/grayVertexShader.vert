#version 330

layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec3 inputColor;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec3 fragColor;

void main() {
    gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vec4(inputPosition, 1.0);
    fragColor = vec3(200, 200, 200);
}