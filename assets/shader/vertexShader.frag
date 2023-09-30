#version 330

layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec3 inputColor;
uniform mat4 mvp;
out vec3 fragColor;

void main() {
    gl_Position = mvp * vec4(inputPosition, 1.0);
    fragColor = inputColor;
}