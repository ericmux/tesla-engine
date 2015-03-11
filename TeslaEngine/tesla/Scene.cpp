//
//  Scene.cpp
//  TeslaEngine
//
//  Created by Eric Muxagata on 3/3/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//

#include "Scene.h"
#include "Director.h"


namespace tesla {

Scene::Scene() : Node() {
   _transform = Director::getInstance()->getViewPortTransform();
};


std::queue<RenderCommand>  Scene::toDrawQueue(){

    std::queue<RenderCommand> cmdQueue;
    
    std::queue<Node*> q;
    q.push(this);
    while(!q.empty()){
        Node* node = q.front();
        q.pop();
        
        cmdQueue.push(node->toRenderCommand());
        
        const std::vector<Node*>& children = node->getChildren();
        for(Node* child : children) q.push(child);
    }
    
    return cmdQueue;
};



};
