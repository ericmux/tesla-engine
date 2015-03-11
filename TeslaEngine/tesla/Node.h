//
//  Node.h
//  TeslaEngine
//
//  Created by Eric Muxagata on 3/3/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//

#ifndef __TeslaEngine__Node__
#define __TeslaEngine__Node__

#include <stdio.h>

#define GLFW_INCLUDE_GLCOREARB
#include <OpenGL/glu.h>
#include <GLFW/glfw3.h>

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "RenderCommand.h"




namespace tesla {

class Node {
protected:
    glm::mat4 _parentToWorldTransform;
    glm::mat4 _transform;
    glm::vec4 _color;
    
    int _zDepth;
    float _width;
    float _height;

    
    Node* _parent;
    std::vector<Node*> _children;

    bool _debugDraw;
    
    
public:
    Node();
    ~Node();
    
    //Methods for local transformation definition.
    void scale(float s);
    void scale(float sx, float sy, float sz);
    void scale(glm::vec3 s);
    
    void translate(glm::vec3 t);
    void rotate(float angle);
    
    void resetTransform();
    inline glm::mat4 getCompleteTransform(){ return _parentToWorldTransform*_transform; };
    inline void setParentToWorldTransform(glm::mat4 M){ _parentToWorldTransform = M; };
    
    inline void setZDepth(int zDepth){ _zDepth = zDepth; };
    inline int getZDepth(){ return _zDepth; };
    
    inline void setWidth(float w){ _width = w; };
    inline float getWidth(){ return _width; };
    
    inline void setHeight(float h){ _height = h; };
    inline float getHeight(){ return _height; };
    
    inline void setColor(float r, float g, float b, float a){ _color = glm::vec4(r,g,b,a); };
    inline glm::vec4 getColor(){ return glm::vec4(_color); };
    
    inline void setParent(Node* parent){ _parent = parent; };
    inline Node* getParent(){ return _parent; };
    
    //Debug draw. A colored quad will be drawn to represent the node.
    inline void setDebugDraw(bool debugDraw){ _debugDraw = debugDraw; };
    
    //Tree methods.
    void addChild(Node* child);
    
    void removeChild(Node* child);
    void removeChildAt(int idx);
    
    void removeFromParent();
    
    inline const std::vector<Node*>& getChildren(){ return _children; };
    
    
    //Convert to RenderCommand.
    virtual RenderCommand toRenderCommand();


};


};



#endif /* defined(__TeslaEngine__Node__) */
