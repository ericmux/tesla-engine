//
//  KeyEvent.h
//  TeslaEngine
//
//  Created by Eric Muxagata on 3/11/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//

#ifndef TeslaEngine_KeyEvent_h
#define TeslaEngine_KeyEvent_h


#include "IEvent.h"

namespace tesla {

class KeyEvent : public IEvent {
public:
    int key;
    int scancode;
    int action;
    int mods;
    
    ~KeyEvent(){};
};


};


#endif
