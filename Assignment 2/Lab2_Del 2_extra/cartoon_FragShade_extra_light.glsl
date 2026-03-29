#version 420 core

#define MAX_LIGHTS 2

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

uniform Light lights[MAX_LIGHTS];
uniform Material material;
uniform vec3 viewPos;

void main(void)
{
    // Normalisering
    vec3 N = normalize(normal);   
    vec3 viewDir = normalize(viewPos - pos);  //Our V

     vec3 finalColor = vec3(0.0);

     for(int i=0; i<MAX_LIGHTS; i++){

     vec3 lightDir = normalize(lights[i].position-pos); //Our L 
    vec3 reflectDir = reflect(-lightDir, N); //Our R

    // Ambient light 
 
    //Iambient = la * ka 
    vec3 ambient = lights[i].ambient * material.ambient;

	

    // Diffus light
    ////Idiffuse = Id*kd * (N.L)
    float NdotL = max(dot(N, lightDir), 0.0);
    
    vec3 diffuse = lights[i].diffuse * material.diffuse * intensity;

    //specular light 
    //Ispecular= Isks(R.V)^shiness

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   vec3 specular = lights[i].specular * material.specular * spec * 0.0;

    float intensity = 0.0;
    intensity = floor(NdotL * 5.0) / 5.0;

  
    
    finalColor += ((ambient + diffuse) * intensity) + specular;
    
    

    }
    fColor = vec4(clamp(finalColor, 0.0, 1.0), 1.0);
}
