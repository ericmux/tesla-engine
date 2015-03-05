//
//  Texture.cpp
//  TeslaEngine
//
//  Created by Eric Muxagata on 3/2/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//

#include "Texture.h"
#include <iostream>


namespace tesla {


void Texture::loadTexture(){
    glGenTextures(1, &_name);
    glBindTexture(GL_TEXTURE_2D, _name);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _texels);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
};

void Texture::deleteTexture(){
    glDeleteTextures(1, &_name);
    _width  = 0;
    _height = 0;
    _name   = 0;
};
  
  
Texture::Texture(std::string fileName){

    _texels = SOIL_load_image(fileName.c_str(), &_width, &_height, 0, SOIL_LOAD_RGB);
    
    if(_texels == NULL){
        std::cout << "Unable to load texture located at: " << fileName << "." << std::endl;
    }
    
    //No error-checking. TO DO.
    loadTexture();

};


Texture::~Texture(){
    deleteTexture();
    SOIL_free_image_data(_texels);
}


void Texture::activate(){
    glBindTexture(GL_TEXTURE_2D, _name);
};
  
  
  
  
};