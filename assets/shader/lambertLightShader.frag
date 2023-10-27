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
uniform int numLights;

// Camera properties
struct Camera {
    vec3 position;  // Position of the camera
};
uniform Camera camera;

out vec4 out_Color;

void main () {
    vec3 finalColor = vec3(0.0);

    // Loop through all lights
    for (int i = 0; i < numLights && i < 4; i++) {
        vec3 lightDir = normalize(lights[i].position - vec3(ex_worldPosition));

        // Diffuse lighting
        float diff = max(dot(lightDir, normalize(ex_worldNormal)), 0.0);
        vec3 diffuceColor = diff * lights[i].color;

        finalColor += diffuceColor;
    }

    // Add the ambient color to the final color
    finalColor += material.ambientColor;

    out_Color = vec4(finalColor * material.objectColor, 1.0);
}