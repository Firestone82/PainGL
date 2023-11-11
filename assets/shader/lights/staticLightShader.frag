#version 400

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
in vec2 ex_tex;
out vec4 out_Color;

// Material properties
struct Material {
    vec3 objectColor;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

// Light properties
struct Light {
    vec3 position;  // Position of the light

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light lights[4];
uniform int numLights;

// Camera properties
struct Camera {
    vec3 position;  // Position of the camera
};
uniform Camera camera;

uniform bool useTexture;
uniform sampler2D textureDiffuse1;
uniform sampler2D textureSpecular1;

void main() {
    vec3 finalColor = material.objectColor;

    // Loop through all lights
    for (int i = 0; i < numLights && i < 4; i++) {
        // Ambient reflection
        vec3 diffuse = lights[i].diffuse * material.diffuse;
        if (useTexture) diffuse *= texture(textureDiffuse1, ex_tex).rgb;

        finalColor += diffuse;
    }

    out_Color = vec4(finalColor, 1.0);
}