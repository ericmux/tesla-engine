//
//  Node.cpp
//  TeslaEngine
//
//  Created by Eric Muxagata on 3/3/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//

#include "Node.h"
#include <iostream>



namespace tesla {

Node::Node() :_zDepth(0), _width(0), _height(0), _parent(nullptr), _debugDraw(false){
    _parentToWorldTransform = glm::mat4();
    _transform = glm::mat4();
    _color = glm::vec4();
    _children = std::vector<Node*>();

};

void Node::setScale(float s){
    _transform = glm::scale(_transform, glm::vec3(s));
};

void Node::translate(glm::vec3 t){
    _transform = glm::translate(_transform, t);
};

void Node::rotate(float angle){
    _transform = glm::rotate(_transform, angle, glm::vec3(0.0f,0.0f,1.0f));
};

void Node::resetTransform(){
    _transform = glm::mat4();
};

void Node::addChild(Node *child){

    assert(child != nullptr);

    if(std::find(_children.begin(), _children.end(), child) != _children.end()){
        std::cout << "Child already added." << std::endl;
    }
    
    if(child->getParent() != nullptr){
        std::cout << "Child already has a parent. Remove it from it first." << std::endl;
    }
    
    child->setParent(this);
    child->setParentToWorldTransform(_parentToWorldTransform*_transform);
    
    _children.push_back(child);

};






};
