//
//  InputHandler.cpp
//  TeslaEngine
//
//  Created by Eric Muxagata on 3/11/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//

#include "InputHandler.h"

namespace tesla {

static InputHandler* _sharedInputHandler;

InputHandler::InputHandler(){};
  
InputHandler* InputHandler::getInstance(){
    if(_sharedInputHandler == nullptr){
        _sharedInputHandler = new InputHandler();
    }

    return _sharedInputHandler;
};
  
  
  
  
};