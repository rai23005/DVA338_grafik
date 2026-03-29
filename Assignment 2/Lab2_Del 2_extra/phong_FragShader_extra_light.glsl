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
const int MAX_LIGHTS = 5;

uniform Light lights[MAX_LIGHTS];
uniform Material material;
uniform vec3 viewPos;
uniform int numLights;


#define VILKETLJUS 1

void main(void)
{
    // Normalisering
     vec3 N = normalize(normal);   
    vec3 viewDir = normalize(viewPos - pos);  //Our V
   

    vec3 finalColor = vec3(0.0);
    vec3 ambient = vec3(0.0);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    vec3 lightDir = vec3(0.0);
    vec3 reflectDir = vec3(0.0);

    //DEBUGG 
    if (numLights == 1) {
    fColor = vec4(1.0,0.0,0.0, 1.0);
    return;
}

     for(int i=1; i<numLights; i++){
    


  
    lightDir = normalize(lights[i].position-pos); //Our L 
    reflectDir = normalize(reflect(-lightDir, N)); //Our R

    // Ambient light 
 
    //Iambient = la * ka 
    ambient = lights[i].ambient * material.ambient;
    
	
    // Diffus light
    ////Idiffuse = Id*kd * (N.L)
    float NdotL = max(dot(N, lightDir), 0.0);
    
    diffuse = lights[i].diffuse * material.diffuse * NdotL;

    //specular light 
    //Ispecular= Isks(R.V)^shiness

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);



    specular = lights[i].specular* material.specular * spec;
   

  finalColor += ambient;  
    finalColor += diffuse;  
finalColor += specular;

   
    }

fColor = vec4(clamp(finalColor, 0.0, 1.0), 1.0);


    }
