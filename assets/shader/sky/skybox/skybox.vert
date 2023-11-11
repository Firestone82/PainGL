#version 400

layout (location = 0) in vec3 position;

out vec3 ex_tex;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main() {
    ex_tex = position;
    gl_Position = (projectionMatrix * viewMatrix * vec4(position, 1.0)).xyww;
}