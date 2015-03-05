//
//  Texture.h
//  TeslaEngine
//
//  Created by Eric Muxagata on 3/2/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//

#ifndef __TeslaEngine__Texture__
#define __TeslaEngine__Texture__

#include <stdio.h>
#include <string>

#define GLFW_INCLUDE_GLCOREARB
#include <OpenGL/glu.h>
#include <GLFW/glfw3.h>

#include "SOIL.h"


namespace tesla {

class Texture {
    private:
        GLuint  _name;
        int     _height;
        int     _width;
        unsigned char*   _texels;
    
        void loadTexture();
        void deleteTexture();
    
    
    
    public:
        Texture(std::string fileName);
        Texture(char* data);
    
        ~Texture();
    
        void activate();

};

  
};




#endif /* defined(__TeslaEngine__Texture__) */
