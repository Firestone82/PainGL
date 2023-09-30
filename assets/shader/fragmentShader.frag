#version 330

in vec3 fragColor;
out vec4 targetColor;

void main() {
    targetColor = vec4(fragColor, 1.0);
}