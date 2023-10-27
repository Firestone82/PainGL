#version 400

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

// Material properties
struct Material {
    vec3 objectColor;   // The color of the object
    vec3 ambientColor;  // The ambient reflection color
    float specular;     // Specular intensity
    float shininess;    // Shininess coefficient
};
uniform Material material;

// Light properties
struct Light {
    vec3 position;  // Position of the light
    vec3 color;     // Color of the light
};
uniform Light lights[4];

// Camera properties
struct Camera {
    vec3 position;  // Position of the camera
};
uniform Camera camera;
uniform int numLights;

out vec4 out_Color;

void main () {
    out_Color = vec4(material.objectColor, 1.0);
}