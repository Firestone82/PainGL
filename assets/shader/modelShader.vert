#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix; //(M-1)T

out vec4 ex_worldPosition;
out vec3 ex_worldNormal;
out vec2 ex_tex;

uniform float scale;

void main(void) {
    ex_worldPosition = modelMatrix * vec4(position, 1.0f);
    ex_worldNormal = normalMatrix * normal;
    ex_tex = tex * scale;

    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(position, 1.0f);
}