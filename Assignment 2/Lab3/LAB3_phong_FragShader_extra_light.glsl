#version 420 core


in vec3 pos;
in vec3 normal;
in vec2 texCoord;

out vec4 fColor;


struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;


    int isSpotLight;
    vec3 direction;

    float constant;
    float linear;
    float quadratic;
    
    float innerCutoff;
    float outerCutoff;
 
    
};


const int MAX_LIGHTS = 100;

uniform Light lights[MAX_LIGHTS];
uniform vec3 viewPos;
uniform int numLights;

uniform Light light;


// Material properties
uniform vec3 materia_Ambient;
uniform vec3 materia_Diffuse;
uniform vec3 materia_Specular;
uniform float materia_Shininess;

//has textur 

uniform sampler2D DiffuseTexture;
uniform sampler2D SpecularTexture;
uniform sampler2D NormalTexture;

//has textur or not 
uniform bool useSpecularTexture;
uniform bool useDiffuseTexture;
uniform bool useNormalTexture;


void main(void)
{
    vec3 N = normalize(normal);
    if (useNormalTexture) {
        vec3 normalTex = texture(NormalTexture, texCoord).rgb;
        N = normalize(normalTex * 2.0 - 1.0);
    }

    vec3 viewDir = normalize(viewPos - pos);
    vec3 finalColor = vec3(0.0);

    for (int i = 0; i < numLights; i++) {
        vec3 lightDir = normalize(lights[i].position - pos);
        vec3 reflectDir = normalize(reflect(-lightDir, N));

        //Ambient
        vec3 ambient = lights[i].ambient * materia_Ambient;

        //Diffuse
         vec3 diffuseColor = materia_Diffuse;
        if(useDiffuseTexture){    
        diffuseColor = texture(DiffuseTexture, texCoord).rgb;}


        float NdotL = max(dot(N, lightDir), 0.0);
        vec3 diffuse = lights[i].diffuse * diffuseColor * NdotL;

        //Specular
            vec3 specularColor = materia_Specular;
            if (useSpecularTexture) {   
        specularColor = texture(SpecularTexture, texCoord).rgb; }

        float spec = pow(max(dot(viewDir, reflectDir), 0.0), materia_Shininess);
        vec3 specular = lights[i].specular * specularColor * spec;



        float attenuation = 1.0;
        float intensity = 1.0;

        //Is spotligt
        if (lights[i].isSpotLight == 1) {
         float theta = dot(lightDir, normalize(-lights[i].direction));
        float epsilon = lights[i].innerCutoff - lights[i].outerCutoff;
         intensity = clamp((theta - lights[i].outerCutoff) / epsilon, 0.0, 1.0);

           
        }
         float distance = length(lights[i].position - pos);
            attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + 
                                 lights[i].quadratic * distance * distance);

        ambient *= attenuation * intensity;
        diffuse *= attenuation * intensity;
        specular *= attenuation * intensity;

        finalColor += ambient + diffuse + specular;
    }

    fColor = vec4(clamp(finalColor, 0.0, 1.0), 1.0);
   
}
