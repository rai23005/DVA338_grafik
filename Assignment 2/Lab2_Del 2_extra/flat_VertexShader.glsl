
#version 420 core

in vec3 vPos;
in vec3 vNorm;


out vec3 pos;
out vec3 normal ; // Skickar facet-normal direkt till fragment shader

uniform mat4 model;
uniform mat4 PV;

void main()
{

   //Transform vertex position from object space to world space
   pos=vec3(model *vec4(vPos,1.0));

  
    normal = normalize(mat3(transpose(inverse(model))) * vNorm); // Transformera normal korrekt

    // Skicka vidare till fragment shader
    gl_Position = PV * vec4(vPos, 1.0);
}