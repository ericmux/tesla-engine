//
//  MouseButtonEvent.h
//  TeslaEngine
//
//  Created by Eric Muxagata on 3/11/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//

#ifndef TeslaEngine_MouseButtonEvent_h
#define TeslaEngine_MouseButtonEvent_h


namespace tesla {

enum class MouseButton {
    LEFT, RIGHT, MIDDLE
};

class MouseButtonEvent {
public:
    double x;
    double y;
    
    ~MouseCursorEvent(){};
};


};

#endif
