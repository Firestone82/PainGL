#version 400

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
in vec2 ex_tex;
out vec4 out_Color;

// Material properties
struct Material {
    vec3 diffuse;
    sampler2D textureDiffuse1;

    vec3 specular;
    sampler2D textureSpecular1;

    bool useTexture; // 0 = false, 1 = true
    float shininess; // Size of the specular highlights
};
uniform Material material;

// Light types
#define POINT_LIGHT 0
#define DIRECTIONAL_LIGHT 1
#define SPOT_LIGHT 2
#define FLASHLIGHT 3

// Light properties
#define MAX_LIGHTS 10
struct Light {
    vec3 position;  // Position of the light
    int type;       // 0 = point, 1 = directional, 2 = spot, 3 = flashlight

    // Directional light properties
    vec3 direction;

    // Point light properties
    float constant;
    float linear;
    float quadratic;

    // Spot light properties
    float cutOff;
    float outerCutOff;

    // Light color properties
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light lights[MAX_LIGHTS];
uniform int numLights;

// Camera properties
struct Camera {
    vec3 position;  // Position of the camera
};
uniform Camera camera;

vec3 calculateLight(Light light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = light.type == DIRECTIONAL_LIGHT ? normalize(-light.direction) : normalize(light.position - ex_worldPosition.xyz);

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * (material.useTexture ? texture(material.textureDiffuse1, ex_tex).rgb : material.diffuse);

    // Attenuation
    float distance = length(light.position - ex_worldPosition.xyz);
    float attenuation = 1.0;
    if (light.type != DIRECTIONAL_LIGHT) {
        attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    }

    // Spot light cone
    float intensity = 1.0;
    if (light.type == SPOT_LIGHT || light.type == FLASHLIGHT) {
        float theta = dot(lightDir, normalize(-light.direction));
        float epsilon = cos(radians(light.cutOff)) - cos(radians(light.outerCutOff));
        intensity = clamp((theta - cos(radians(light.outerCutOff))) / epsilon, 0.0, 1.0);
    }

    return diffuse * attenuation * intensity;
}

void main() {
    vec3 viewDir = normalize(camera.position - vec3(ex_worldPosition));
    vec3 normal = normalize(ex_worldNormal);

    vec3 finalColor = vec3(0.0);
    for (int i = 0; i < numLights && i < MAX_LIGHTS; i++) {
        finalColor += calculateLight(lights[i], normal, viewDir);
    }

    out_Color = vec4(finalColor, 1.0);
}