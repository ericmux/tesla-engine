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


namespace tesla {

class Director{

    private:
        Renderer* _renderer;
        GLFWwindow* _mainWindow;
        std::string _gameName;
        Scene* _currentScene;
        float _animationInterval;
    
        int _width;
        int _height;
    
        Director();
    
    public:
    
        //Default screen dimensions in pixels.
        static const int DEFAULT_WIDTH  = 1440;
        static const int DEFAULT_HEIGHT = 900;
    
        static Director* getInstance();
        void operator=(Director const&);
    
        //Initializes GLFW with the specified window size.
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
