//
//  RenderCommand.h
//  TeslaEngine
//
//  Created by Eric Muxagata on 3/2/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//

#ifndef __TeslaEngine__RenderCommand__
#define __TeslaEngine__RenderCommand__

#define GLFW_INCLUDE_GLCOREARB
#include <OpenGL/glu.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <vector>
#include "Texture.h"

namespace tesla {

class RenderCommand {
public:
    Texture *targetTexture;
    std::vector<float>  bufferVBO;
    std::vector<GLuint> bufferEBO;
};

};

#endif
