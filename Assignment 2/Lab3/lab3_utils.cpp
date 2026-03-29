
#include "lab3_utils.h"
#include "shader_utils.h"

//Better to add and switch diffrent shader program 
ShaderNode* shaderList = NULL;
ShaderNode* activeShader = NULL;

//To add shader to a list
void addShader(const char* name, const char* vertexPath, const char* fragmentPath) {
    ShaderNode* node = (ShaderNode*)malloc(sizeof(ShaderNode));
    node->programID = LoadShaderProgram(vertexPath, fragmentPath);
    node->name = name;
    node->next = shaderList;
    shaderList = node;

    if (activeShader == NULL) {
        activeShader = node;
        activeShaderProgram = node->programID;
        glUseProgram(activeShaderProgram);
    }
}


//Switch shader 
void switchToNextShader() {
    if (activeShader && activeShader->next) {
        activeShader = activeShader->next;
    }
    else {
        activeShader = shaderList;  
    }
    activeShaderProgram = activeShader->programID;
    glUseProgram(activeShaderProgram);
}


//To load a model 
obj* load_obj_model(const char* filepath) {
    obj* model = obj_create(filepath);
    if (!model) {
        printf("Could not load OBJ file: %s\n", filepath);
       return NULL;
    }

    obj_proc(model);
    return model;
}


// Add the objekt to a list 
void add_obj_to_list(obj* model, const char* modelname,int id,
    Vector translation,Vector rotation,Vector vectorScale,
    Vector translationPerFrame, Vector rotationPerFrame, Vector scalePerFrame,
    int animationMaxLengthFrame, int offsetFrame)
{
    if (objectCount >= MAX_OBJECTS) {
        std::cout << "The limit of Objects, incresse the the MAX_OBJECTS value" << std::endl;
        return;
    }

    ObjNode* node = &objectArray[objectCount];

   
    node->model = model;

    node->modelname = modelname;
    node->id = id;

    //Where to put model 
    node->translation = translation;
    node->rotation = rotation;
    node->scale = vectorScale;

    //Animations value 
    node->rotationPerFrame= rotationPerFrame;
    node->scalePerFrame = scalePerFrame;

    node->translationPerFrame = translationPerFrame;
    node->animationMaxLengthFrame = animationMaxLengthFrame;
    node->offsetFrame = offsetFrame;

    objectCount++;
}



//Set material value for each surface 
void SetObjMaterialUniforms(GLuint shaderProgram, obj* model) {

    if (!model || !model->materialArr) return;

    obj_mtrl* mat = &model->materialArr[0]; 

    // Ambient (Ka)
    if (model->cloc[OBJ_KA] != -1)
    {
 
    glUniform3fv(model->cloc[OBJ_KA], 1, mat->kv[OBJ_KA].c);
    }


    // Diffuse (Kd)
    if (model->cloc[OBJ_KD] != -1){ 
        glUniform3fv(model->cloc[OBJ_KD], 1, mat->kv[OBJ_KD].c);
    }

    // Specular (Ks)
    if (model->cloc[OBJ_KS] != -1)
        glUniform3fv(model->cloc[OBJ_KS], 1, mat->kv[OBJ_KS].c);

    // Shininess (Ns)
    if (model->cloc[OBJ_NS] != -1)
    {
       
        //glUniform1f(model->cloc[OBJ_NS], mat->kv[OBJ_NS].c[0]);
        glUniform1f(model->cloc[OBJ_NS], 64.0f);
       
    }

       

    // Diffuse Texture
    if (model->oloc[OBJ_KD] != -1 && mat->kv[OBJ_KD].map > 0) {
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mat->kv[OBJ_KD].map);
        glUniform1i(model->oloc[OBJ_KD], 0);
    }

    // Specular Texture
    if (model->oloc[OBJ_KS] != -1 && mat->kv[OBJ_KS].map > 0) {
      
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, mat->kv[OBJ_KS].map);
        glUniform1i(model->oloc[OBJ_KS], 1);
    }

    //Diffrent lock, if have texture or not 
    GLint locSpec = glGetUniformLocation(shaderProgram, "useSpecularTexture");
    glUniform1i(locSpec, (mat->kv[OBJ_KS].map > 0));
        
    GLint locDiffuse = glGetUniformLocation(shaderProgram, "useDiffuseTexture");
    glUniform1i(locDiffuse, (mat->kv[OBJ_KD].map > 0));
        
    GLint locNormal = glGetUniformLocation(shaderProgram, "useNormalTexture");
    glUniform1i(locNormal, (mat->kv[OBJ_KN].map > 0));



    // Normal Texture
    if (model->oloc[OBJ_KN] != -1 && mat->kv[OBJ_KN].map > 0) {
        
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, mat->kv[OBJ_KN].map);
        glUniform1i(model->oloc[OBJ_KN], 2);
    }

}

//Prepare the model
void prepare_obj(obj* model, GLuint shaderProgram) {
    obj_set_vert_loc(
        model,
        -1,
        glGetAttribLocation(shaderProgram, "vNorm"),
        glGetAttribLocation(shaderProgram, "vTexCoord"),
        glGetAttribLocation(shaderProgram, "vPos")
    );

   

    obj_set_prop_loc(model, OBJ_KA, 
        glGetUniformLocation(shaderProgram, "materia_Ambient"), -1, -1);

    obj_set_prop_loc(model, OBJ_KD,
        glGetUniformLocation(shaderProgram, "materia_Diffuse"),
        glGetUniformLocation(shaderProgram, "DiffuseTexture"),
        -1);

    obj_set_prop_loc(model, OBJ_KS,
        glGetUniformLocation(shaderProgram, "materia_Specular"),
        glGetUniformLocation(shaderProgram, "SpecularTexture"),
        -1);

     obj_set_prop_loc(model, OBJ_KN,  
        -1,
        glGetUniformLocation(shaderProgram, "NormalTexture"),
        -1);

    obj_set_prop_loc(model, OBJ_NS, 
        glGetUniformLocation(shaderProgram, "materia_Shininess"), -1, -1);
}



//That get a loop for frame 
int getanimateFrameloop(int animationMaxLengthFrame, int currentFrame, int offsetFrame) {
    if (animationMaxLengthFrame <= 0) return 0;
    int localFrame = (currentFrame + offsetFrame) % animationMaxLengthFrame;

    return localFrame;

};


//Get a vector that that cal animate vector
Vector animateVector(Vector base, Vector perfram, int frame) {

    Vector result;
    result.x = base.x + perfram.x * frame;
    result.y = base.y + perfram.y * frame;
    result.z = base.z + perfram.z * frame;

    return result;

}

//That you will only rotae in 0-360 degree
float rotationWrapDegree(float degree) {
    while (degree >= 360.0f) {
        degree -= 360.0f;
    }
    while (degree < 0.0f) {
        degree += 360.0f;
    }
    return degree;
}

Vector rationWrapVector(Vector base, Vector perfram, int frame) {


    Vector result;
    result.x = rotationWrapDegree(base.x + perfram.x * frame);
    result.y = rotationWrapDegree(base.y + perfram.y * frame);
    result.z = rotationWrapDegree(base.z + perfram.z * frame);

    return result;

}

