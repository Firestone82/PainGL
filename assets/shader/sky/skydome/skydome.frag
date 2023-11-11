#version 400

in vec2 ex_tex;
out vec4 out_Color;

uniform sampler2D skyTexture;

void main() {
    out_Color = texture(skyTexture, ex_tex);
}
