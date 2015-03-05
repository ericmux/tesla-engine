#include "RenderEngine.h"

#include <unistd.h>
#include <errno.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>


#define GLFW_INCLUDE_GLCOREARB
#include <OpenGL/glu.h>
#include <GLFW/glfw3.h>


#include "SOIL.h"

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Texture.h"



GLFWwindow* mainWindow;

GLuint vbo, ebo;
GLuint shaderProgram;
GLint uniColor;
GLint uniRot;


//textures.
tesla::Texture *tex1;
tesla::Texture *tex2;
bool choose_tex = true;


//vbo data.
float vs[] = {
    0.5f,   0.5f,   1.0f,0.0f,0.0f,  1.0f,1.0f,
    0.5f,   -0.5f,  0.0f,1.0f,0.0f,  1.0f,0.0f,
    -0.5f,   0.5f,  0.0f,0.0f,1.0f,  0.0f,1.0f,
    -0.5f,  -0.5f,  1.0f,1.0f,1.0f,  0.0f,0.0f
};

//ebo data.
GLuint es[] = {
    0,2,1,
    2,3,1
};

static float t = 0.0f;
const float dt = 0.05f;

void print_vector(glm::vec3 v){
    std::cout << "(" << v.x << "," << v.y << "," << v.z << ")" << std::endl;
}

void write_to_vbo(std::vector<float>& verts){

    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(float), verts.data(), GL_DYNAMIC_DRAW);

}

void write_to_ebo(std::vector<GLuint>& idxs){

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, idxs.size()*sizeof(GLuint), idxs.data(), GL_DYNAMIC_DRAW);

}

 
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
    
    t += dt;
    if(t > 10.0f){
        t = 0.0f;
        if(choose_tex) tex1->activate();
        else tex2->activate();
        
        choose_tex = !choose_tex;
    }
    
    //need to refresh buffers before changing textures.
    std::vector<float> verts(vs, vs + sizeof(vs)/sizeof(float));
    write_to_vbo(verts);
    
    std::vector<GLuint> idxs(es, es + sizeof(es)/sizeof(GLuint));
    write_to_ebo(idxs);
    
    //Updating rotation.
    glm::mat4 rot;
    rot = glm::translate(rot, glm::vec3(0.1f,0.2f,0.3f));
    
    for(int i = 0; i < rot.length(); i++){
        
        for(int j = 0; j < rot[i].length(); j++){
            std::cout << rot[i][j] << " ";
        }
    }
    std::cout << std::endl;
    
    rot = glm::rotate(rot, glm::radians(20*t), glm::vec3(0.0f,0.0f,1.0f));
    glUniformMatrix4fv(uniRot, 1, GL_FALSE, glm::value_ptr(rot));
    
    //Draw triangles.
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
   
    
    
    std::this_thread::sleep_for(std::chrono::milliseconds(5));

}

int pcwd() {
   char cwd[1024];
   if (getcwd(cwd, sizeof(cwd)) != NULL)
       fprintf(stdout, "Current working dir: %s\n", cwd);
   else
       perror("getcwd() error");
   return 0;
}

void check_compile_status(GLuint shader){
    GLint ret;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
    if(ret != GL_TRUE){
        std::cout << "Shader" << shader << "failed to compile. Compile log:" << std::endl;
        char buffer[512];
        glGetShaderInfoLog(shader, sizeof(buffer), NULL,buffer);
        
        std::cout << std::string(buffer) << std::endl;
        
        return;
    }

}


void compile_shaders(){

    pcwd();

    std::ifstream vtx_shader("TeslaEngine/shaders/hw_shader.vert");
    if(vtx_shader.fail()){
        std::cout << "Vtx shader was not found." << std::endl;
        return;
    }
    
    
    std::ifstream frag_shader("TeslaEngine/shaders/hw_shader.frag");
    if(frag_shader.fail()){
        std::cout << "Frag shader was not found." << std::endl;
        return;
    }
    
    
    std::cout << "OpenGL/GLSL versions: " << std::endl;
    std::cout << std::string((char *)glGetString(GL_VERSION)) << std::endl;
    std::cout << std::string((char *)glGetString(GL_SHADING_LANGUAGE_VERSION)) << std::endl;
    
    
    std::stringstream vtxss, fragss;
    vtxss << vtx_shader.rdbuf();
    fragss << frag_shader.rdbuf();
    
    GLuint vtxi, fragi;
    
    std::string vtx_shader_str(vtxss.str());
    char* vtx_shader_raw[] = { (char *)vtx_shader_str.c_str() };
    
    vtxi = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vtxi, 1, vtx_shader_raw, NULL);
    glCompileShader(vtxi);
    
    //Check success
    check_compile_status(vtxi);
    
    std::string frag_shader_str(fragss.str());
    char* frag_shader_raw[] = { (char *)frag_shader_str.c_str() };
    
    fragi = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragi, 1, frag_shader_raw, NULL);
    glCompileShader(fragi);
    
    //Check success
    check_compile_status(fragi);
    
    
    //Create shader program.
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vtxi);
    glAttachShader(shaderProgram, fragi);
    
    glBindFragDataLocation(shaderProgram, 0, "outColor");

}

void glfw_use_opengl_core_profile(){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

 
/* Main function: GLUT runs as a console application starting at main()  */
int init_opengl(int argc, char **argv) {

    if (!glfwInit()) exit(EXIT_FAILURE);
    
    glfw_use_opengl_core_profile();
    
    int w = 1440;
    int h = 900;

    mainWindow = glfwCreateWindow(h, w, "Tesla Engine", NULL, NULL);
    if (!mainWindow){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(mainWindow);
    
    
    
    //vao.
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    std::vector<float> verts(vs, vs + sizeof(vs)/sizeof(float));
    
    glGenBuffers(1, &vbo);
    write_to_vbo(verts);
    
    std::vector<GLuint> idxs(es, es + sizeof(es)/sizeof(GLuint));
    
    glGenBuffers(1, &ebo);
    write_to_ebo(idxs);
    
    GLuint err = glGetError();
    if(err != 0){
        std::cout << "Error at VBO/VAO with code: "<< err << std::endl;
        std::cout << gluErrorString(err) << std::endl;
    }
    
    //shaders.
    compile_shaders();
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    
    err = glGetError();
    if(err != 0){
        std::cout << "Error at Shader Compilation with code: "<< err << std::endl;
        std::cout << gluErrorString(err) << std::endl;
    }
    
    //pos attribute.
    GLuint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0);
    
    //Color attribute.
    GLuint colorAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colorAttrib);
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*) (2*sizeof(float)));
    
    //Texcoord atrribute.
    GLuint texAttrib = glGetAttribLocation(shaderProgram, "vUV");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*) (5*sizeof(float)));
    
    
    err = glGetError();
    if(err != 0){
        std::cout << "Error at Attribute Enabling with code: "<< err << std::endl;
        std::cout << gluErrorString(err) << std::endl;
    }
    
    
    //Using my Texture class.
    tex1 = new tesla::Texture("TeslaEngine/test/textures/octobiwan.jpg");
    tex2 = new tesla::Texture("TeslaEngine/test/textures/joff_pic.jpg");
    
    
    //Uniform variable.
    uniRot = glGetUniformLocation(shaderProgram, "rot");
    
    while (!glfwWindowShouldClose(mainWindow)){
        int width, height;
        glfwGetFramebufferSize(mainWindow, &width, &height);

        glViewport(0, 0, width, height);

        display();
    
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }
    
    delete tex1;
    delete tex2;
    
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    
    return 0;
}
