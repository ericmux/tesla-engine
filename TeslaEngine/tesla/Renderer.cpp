//
//  Renderer.cpp
//  TeslaEngine
//
//  Created by Eric Muxagata on 2/22/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include <new>
#include <iostream>
#include <fstream>
#include <sstream>


#define GLFW_INCLUDE_GLCOREARB
#include <OpenGL/glu.h>
#include <GLFW/glfw3.h>


#include "Renderer.h"



namespace tesla {

#define VTX_SHADER_PATH "TeslaEngine/shaders/hw_shader.vert"
#define FRAG_SHADER_PATH "TeslaEngine/shaders/hw_shader.frag"


static Renderer* _sharedRenderer = nullptr;


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


void Renderer::compile_shaders(){

    pcwd();

    std::ifstream vtx_shader(VTX_SHADER_PATH);
    if(vtx_shader.fail()){
        std::cout << "Vtx shader was not found." << std::endl;
        return;
    }
    
    
    std::ifstream frag_shader(FRAG_SHADER_PATH);
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
    
    
    std::string vtx_shader_str(vtxss.str());
    char* vtx_shader_raw[] = { (char *)vtx_shader_str.c_str() };
    
    _vtxi = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(_vtxi, 1, vtx_shader_raw, NULL);
    glCompileShader(_vtxi);
    
    //Check success
    check_compile_status(_vtxi);
    
    std::string frag_shader_str(fragss.str());
    char* frag_shader_raw[] = { (char *)frag_shader_str.c_str() };
    
    _fragi = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_fragi, 1, frag_shader_raw, NULL);
    glCompileShader(_fragi);
    
    //Check success
    check_compile_status(_fragi);
    
    
    //Create shader program.
    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, _vtxi);
    glAttachShader(_shaderProgram, _fragi);
    
    glBindFragDataLocation(_shaderProgram, 0, "outColor");

}




Renderer::Renderer(){
    // VAO.
    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);
    
    
    // VBO/EBO.
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);
    
    
    //shaders.
    compile_shaders();
    glLinkProgram(_shaderProgram);
    glUseProgram(_shaderProgram);
    
    
    GLenum err = glGetError();
    if(err != 0){
        std::cout << "Error at Shader Compilation with code: "<< err << std::endl;
        std::cout << gluErrorString(err) << std::endl;
    }
    
    //pos attribute.
    GLuint posAttrib = glGetAttribLocation(_shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0);
    
    //Color attribute.
    GLuint colorAttrib = glGetAttribLocation(_shaderProgram, "color");
    glEnableVertexAttribArray(colorAttrib);
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*) (2*sizeof(float)));
    
    //Texcoord atrribute.
    GLuint texAttrib = glGetAttribLocation(_shaderProgram, "vUV");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*) (5*sizeof(float)));
    
    
    err = glGetError();
    if(err != 0){
        std::cout << "Error at Attribute Enabling with code: "<< err << std::endl;
        std::cout << gluErrorString(err) << std::endl;
    }



};


Renderer* Renderer::getInstance(){

    if(_sharedRenderer == nullptr){
        _sharedRenderer = new (std::nothrow) Renderer();
    }
    
    return _sharedRenderer;

};




};






