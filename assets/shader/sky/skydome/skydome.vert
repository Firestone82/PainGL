#version 400

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec2 ex_tex;

void main() {
    gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0);
    ex_tex = tex;
}