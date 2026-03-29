#version 420 core

in vec3 normal;

out vec4 fColor;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Light light;
uniform Material material;
uniform vec3 viewPos;

void main(void)
{

    vec3 lightDir = normalize(light.position - viewPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    // Ambient
    vec3 ambient = light.ambient * material.ambient;

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * material.diffuse * diff;

    // Specular
    float spec = pow(max(dot(reflectDir, normalize(viewPos)), 0.0), material.shininess);
    vec3 specular = light.specular * material.specular * spec;

    // Slutlig färg
    vec3 result = ambient + diffuse + specular;
    fColor = vec4(clamp(result, 0.0, 1.0), 1.0);
}