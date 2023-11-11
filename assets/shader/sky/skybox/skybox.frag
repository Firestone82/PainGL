#version 400

in vec3 ex_tex;
out vec4 out_Color;

uniform samplerCube skyTexture;

void main() {
    out_Color = texture(skyTexture, ex_tex);
}