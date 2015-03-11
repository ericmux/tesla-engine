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

Node::~Node(){};

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

void Node::removeChild(Node* child){

    assert(child != nullptr);
    
    auto it = std::find(_children.begin(), _children.end(), child);

    if(it != _children.end()){
        std::cout << "There is no such child." << std::endl;
    }
    
    _children.erase(it);
    
    child->setParent(nullptr);
    child->setParentToWorldTransform(glm::mat4());

};

void Node::removeChildAt(int idx){
    removeChild(_children[idx]);
};

void Node::removeFromParent(){
    
    if(_parent == nullptr) return;
    
    _parent->removeChild(this);

};

RenderCommand Node::toRenderCommand(){
    RenderCommand cmd;
    
    glm::vec4 vtxs[4];
    
    vtxs[0]  = glm::vec4(0.0f,0.0f,0.0f,1.0f);
    vtxs[1]  = glm::vec4(0.0f,_height,0.0f,1.0f);
    vtxs[2]  = glm::vec4(_width,_height,0.0f,1.0f);
    vtxs[3]  = glm::vec4(_width,0.0f,0.0f,1.0f);
    
    glm::mat4 M = _parentToWorldTransform*_transform;
    for(auto& v: vtxs) v = M*v;
    
    
    
    float vtxs_ndc[4*8] = {
        vtxs[0][0],   vtxs[0][1],       _color.r, _color.g, _color.b,  _color.a,    0.0f,1.0f,
        vtxs[1][0],   vtxs[1][1],       _color.r, _color.g, _color.b,  _color.a,    0.0f,0.0f,
        vtxs[2][0],   vtxs[2][1],       _color.r, _color.g, _color.b,  _color.a,    1.0f,0.0f,
        vtxs[3][0],   vtxs[3][1],       _color.r, _color.g, _color.b,  _color.a,    1.0f,1.0f
    };
    
    GLuint idxs[2*3] = {
        0,1,2,
        0,2,3
    };
    
    cmd.targetTexture = nullptr;
    
    cmd.bufferVBO = std::vector<float>(vtxs_ndc, vtxs_ndc + sizeof(vtxs_ndc)/sizeof(float));
    cmd.bufferEBO = std::vector<GLuint>(idxs, idxs + sizeof(idxs)/sizeof(GLuint));
    
    return cmd;
};






};
