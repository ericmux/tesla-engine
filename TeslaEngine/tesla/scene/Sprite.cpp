//
//  Sprite.cpp
//  TeslaEngine
//
//  Created by Eric Muxagata on 3/3/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//

#include "Sprite.h"


namespace tesla {


Sprite::Sprite(Texture* tex) : Node() {
    _texture    = tex;
    _height     = _texture->height();
    _width      = _texture->width();
};


RenderCommand Sprite::toRenderCommand(){
    RenderCommand cmd = Node::toRenderCommand();
    cmd.targetTexture = _texture;

    return cmd;
};


};
