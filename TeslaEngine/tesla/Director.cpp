//
//  Director.cpp
//  TeslaEngine
//
//  Created by Eric Muxagata on 2/22/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//


#include <cstdlib>
#include <new>
#include <chrono>
#include <thread>

#define GLFW_INCLUDE_GLCOREARB
#include <OpenGL/glu.h>
#include <GLFW/glfw3.h>



#include "Director.h"



namespace tesla {

static Director* _sharedDirector = nullptr;
  
  
Director::Director(){

    _renderer = nullptr;
    _mainWindow = nullptr;
    _animationInterval = 1.0f/60.0f;
    _width = 0;
    _height = 0;
    _viewPortTransform = glm::mat4();
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
    
    int w,h;
    glfwGetFramebufferSize(_mainWindow, &w, &h);
    _width = w;
    _height = h;
    
    
    
    
    //make viewPort matrix.
    float m[] = {
        2.0f/_width, 0.0f, 0.0f, -1.0f,
        0.0f, -2.0f/_height, 0.0f,1.0f,
        0.0f,0.0f,1.0f,0.0f,
        0.0f,0.0f,0.0f,1.0f
    };
    _viewPortTransform = glm::transpose(glm::make_mat4(m));
    
    _renderer = Renderer::getInstance();
    
    //Adjust viewPort size.
    glViewport(0, 0, _width, _height);

};

void Director::initOpenGL(){
    initOpenGL(DEFAULT_WIDTH, DEFAULT_HEIGHT);
};

void Director::setGameName(std::string& name){
    if (!_mainWindow) exit(EXIT_FAILURE);
    
    glfwSetWindowTitle(_mainWindow, name.c_str());
    _gameName = name;
};


void Director::run(){

    std::chrono::time_point<std::chrono::system_clock> start, end;

    while (!glfwWindowShouldClose(_mainWindow)){
    
        start = std::chrono::system_clock::now();
        
        //Handle input.
        glfwPollEvents();
        
        //Update physics.
        
        //Render scene graph.
        if(_currentScene){
            std::queue<RenderCommand> cmdQueue = _currentScene->toDrawQueue();
            _renderer->render(&cmdQueue);
        }
        
        std::chrono::duration<double> sleepTime = std::chrono::system_clock::now() - start;
        double dSleepTime = sleepTime.count();
        
        if(dSleepTime < _animationInterval){
            long long usleep_time = 1000*(_animationInterval - dSleepTime);
            std::this_thread::sleep_for(std::chrono::milliseconds(usleep_time));
        }
        
        glfwSwapBuffers(_mainWindow);
    }

};
  
  
  
};
