#version 400

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
in vec2 ex_tex;
out vec4 out_Color;

// Material properties
struct Material {
    vec3 diffuse;
};
uniform Material material;

void main() {
    out_Color = vec4(material.diffuse, 1.0);
}