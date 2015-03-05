//
//  Director.cpp
//  TeslaEngine
//
//  Created by Eric Muxagata on 2/22/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//


#include <cstdlib>
#include <new>

#define GLFW_INCLUDE_GLCOREARB
#include <OpenGL/glu.h>
#include <GLFW/glfw3.h>

#include "Director.h"



namespace tesla {

static Director* _sharedDirector = nullptr;
  
  
Director::Director(){
    _renderer = Renderer::getInstance();
    _mainWindow = nullptr;
    _animationInterval = 1/60.0f;
};
  
  
Director* Director::getInstance(){
    
    if(_sharedDirector == nullptr){
        _sharedDirector = new (std::nothrow) Director();
    }
    
    return _sharedDirector;

};


void Director::initOpenGL(int width,  int height){
    if (!glfwInit()) exit(EXIT_FAILURE);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _mainWindow = glfwCreateWindow(width, height, "Tesla Engine", NULL, NULL);
    if (!_mainWindow){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(_mainWindow);
    
    //Adjust viewPort size.
    int w,h;
    glfwGetFramebufferSize(_mainWindow, &w, &h);
    glViewport(0, 0, w, h);

};

void Director::initOpenGL(){
    initOpenGL(DEFAULT_WIDTH, DEFAULT_HEIGHT);
};

void Director::setGameName(std::string& name){
    if (!_mainWindow) exit(EXIT_FAILURE);
    
    glfwSetWindowTitle(_mainWindow, name.c_str());
    _gameName = name;
};


//vbo data.
float vs1[] = {
    0.5f,   0.5f,   1.0f,0.0f,0.0f,  1.0f,1.0f,
    0.5f,   -0.5f,  0.0f,1.0f,0.0f,  1.0f,0.0f,
    -0.5f,   0.5f,  0.0f,0.0f,1.0f,  0.0f,1.0f,
    -0.5f,  -0.5f,  1.0f,1.0f,1.0f,  0.0f,0.0f
};

float vs2[] = {
    0.5f,   -0.5f,   1.0f,0.0f,0.0f,  1.0f,1.0f,
    0.5f,   -1.0f,  0.0f,1.0f,0.0f,  1.0f,0.0f,
    0.0f,   -0.5f,  0.0f,0.0f,1.0f,  0.0f,1.0f,
    0.0f,  -1.0f,  1.0f,1.0f,1.0f,  0.0f,0.0f
};

//ebo data.
GLuint es[] = {
    0,2,1,
    2,3,1
};


void Director::run(){

    Texture* tex1 = new tesla::Texture("TeslaEngine/test/textures/octobiwan.jpg");
    Texture* tex2 = new tesla::Texture("TeslaEngine/test/textures/joff_pic.jpg");

    std::queue<RenderCommand> queue;
    RenderCommand octCmd, joffCmd;
    
    octCmd.targetTexture = tex1;
    octCmd.bufferVBO = std::vector<float>(vs1, vs1 + sizeof(vs1)/sizeof(float));
    octCmd.bufferEBO = std::vector<GLuint>(es, es + sizeof(es)/sizeof(GLuint));
    
    
    joffCmd.targetTexture = tex2;
    joffCmd.bufferVBO = std::vector<float>(vs2, vs2 + sizeof(vs2)/sizeof(float));
    joffCmd.bufferEBO = std::vector<GLuint>(es, es + sizeof(es)/sizeof(GLuint));
    
    queue.push(octCmd);
    queue.push(joffCmd);
    

    while (!glfwWindowShouldClose(_mainWindow)){

        _renderer->render(queue);
    
        glfwSwapBuffers(_mainWindow);
        glfwPollEvents();
    }

};
  
  
  
};
