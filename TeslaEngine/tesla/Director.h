//
//  Director.h
//  TeslaEngine
//
//  Created by Eric Muxagata on 2/22/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//

#ifndef __TeslaEngine__Director__
#define __TeslaEngine__Director__

#include <stdio.h>
#include <string>

#include "Renderer.h"
#include "Scene.h"

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace tesla {

class Director{
private:
    Renderer* _renderer;
    GLFWwindow* _mainWindow;
    std::string _gameName;
    Scene* _currentScene;
    float _animationInterval;
    glm::mat4   _viewPortTransform;

    int _width;
    int _height;

    Director();

public:
    //Default screen dimensions in pixels.
    static const int DEFAULT_WIDTH  = 1440;
    static const int DEFAULT_HEIGHT = 900;
    
    inline glm::mat4 getViewPortTransform(){ return glm::mat4(_viewPortTransform); };

    inline int getDisplayWidthInPixels()   { return _width;  };
    inline int getDisplayHeightInPixels()  { return _height; };
    

    static Director* getInstance();
    void operator=(Director const&);
    
    inline void setCurrentScene(Scene* scene){ _currentScene = scene; };

    //Initializes GLFW with the specified window size (in GLFW screen coordinates).
    void initOpenGL(int width, int height);

    //Initializes GLFW with a default window size of 1440x900.
    void initOpenGL();

    //Names the rendering window.
    void setGameName(std::string& name);

    //Start rendering.
    void run();

};




};


#endif
