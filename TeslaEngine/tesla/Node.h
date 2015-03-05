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




namespace tesla {

class Node {
private:
    glm::mat4 _parentToWorldTransform;
    glm::mat4 _transform;
    glm::vec3 _color;
    
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
    void setScale(float s);
    void translate(glm::vec3 t);
    void rotate(float radians);
    
    void resetTransform();
    
    inline void setZDepth(int zDepth){ _zDepth = zDepth; };
    inline int getZDepth(){ return _zDepth; };
    
    inline void setWidth(float w){ _width = w; };
    inline float getWidth(){ return _width; };
    
    inline void setHeight(float h){ _height = h; };
    inline float getHeight(){ return _height; };
    
    inline void setColor(float r, float g, float b);
    inline glm::vec3 getColor(){ return glm::vec3(_color); };
    
    //Debug draw. A colored quad will be drawn to represent the node.
    inline void setDebugDraw(bool debugDraw){ _debugDraw = debugDraw; };
    
    
    
    
    
    
    
    
    
    
    



};


};



#endif /* defined(__TeslaEngine__Node__) */
