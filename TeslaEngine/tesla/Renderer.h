//
//  Renderer.h
//  TeslaEngine
//
//  Created by Eric Muxagata on 2/22/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//

#ifndef TeslaEngine_Renderer_h
#define TeslaEngine_Renderer_h

#include <queue>
#include "RenderCommand.h"

namespace tesla {
  
class Renderer {
private:
    GLuint _VAO;
    GLuint _vtxi;
    GLuint _fragi;
    GLuint _shaderProgram;

    GLuint _VBO;
    GLuint _EBO;

    Renderer();
    void operator=(Renderer const&);

    void compileShaders();
  
  
public:
    static Renderer* getInstance();

    //Render a frame based on geometry defined by render commands.
    void render(std::queue<RenderCommand>* cmdQueue);
  
};
  
  
};





#endif
