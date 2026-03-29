#version 420 core

//Local pos/normal
in vec3 vPos;
in vec3 vNorm;

//For add textur 
in vec2 vTexCoord;

//Pos/norm in word space
out vec3 pos;
out vec3 normal;

out vec2 texCoord;



//Matrix to transform codinate 
uniform mat4 model;
uniform mat4 view;
uniform mat4 PV;

void main(void)
{
   
   //Transform vertex position from object space to world space
   pos=vec3(model *vec4(vPos,1.0));

   //Transform normal from object space to world space,
  normal = normalize(mat3(transpose(inverse(model))) * vNorm);

  
  texCoord = vTexCoord;

   // Where the is in world 
    gl_Position = PV * vec4(vPos, 1.0);




}
