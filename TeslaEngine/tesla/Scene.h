//
//  Scene.h
//  TeslaEngine
//
//  Created by Eric Muxagata on 3/3/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//

#ifndef __TeslaEngine__Scene__
#define __TeslaEngine__Scene__

#include <stdio.h>
#include <queue>

#include "Node.h"
#include "RenderCommand.h"


namespace tesla {
  

class Scene : public Node {
private:


public:
    Scene();
    
    //traverse convert all objects in the scene to render commands.
    std::queue<RenderCommand> toDrawQueue();



};
  
  
  
  
  
};





#endif
