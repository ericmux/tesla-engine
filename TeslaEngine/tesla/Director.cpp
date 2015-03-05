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

};

void Director::initOpenGL(){
    initOpenGL(DEFAULT_WIDTH, DEFAULT_HEIGHT);
};

void Director::setGameName(std::string& name){
    if (!_mainWindow) exit(EXIT_FAILURE);
    
    glfwSetWindowTitle(_mainWindow, name.c_str());
    _gameName = name;
};
  
  
  
};
