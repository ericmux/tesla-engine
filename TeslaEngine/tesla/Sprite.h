//
//  Sprite.h
//  TeslaEngine
//
//  Created by Eric Muxagata on 3/3/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//

#ifndef __TeslaEngine__Sprite__
#define __TeslaEngine__Sprite__

#include <stdio.h>

#include "Node.h"
#include "Texture.h"

namespace tesla {

class Sprite : public Node {
private:
    Texture* _texture;
    
public:
    Sprite(Texture* tex);


    //Convert to RenderCommand.
    RenderCommand toRenderCommand();

};


};


#endif
