//
//  Sprite.cpp
//  TeslaEngine
//
//  Created by Eric Muxagata on 3/3/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//

#include "Sprite.h"


namespace tesla {

RenderCommand Sprite::parseToRenderCommand(){
    RenderCommand cmd = Node::parseToRenderCommand();
    cmd.targetTexture = _texture;

    return cmd;
};


};
