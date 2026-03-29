#version 420 core


in vec3 pos;
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

vec3 N = normalize(normal);
vec3 lightDir = normalize(light.position-pos); //Our L 
vec3 viewDir = normalize(viewPos - pos);  //Our V
 vec3 reflectDir = reflect(-lightDir, N); //Our R


//Iambient = la * ka 
vec3 ambient = light.ambient * material.ambient;


//Idiffuse = Id*kd * (N.L)

   float NdotL = max(dot(N, lightDir), 0.0);
	vec3 diffuse = light.diffuse * material.diffuse * NdotL;

//Ispecular= Isks(R.V)^shiness

float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
vec3 specular = light.specular * material.specular * spec;

    vec3 finalColor = ambient+ diffuse + specular;


    fColor = vec4(finalColor, 1.0);

}