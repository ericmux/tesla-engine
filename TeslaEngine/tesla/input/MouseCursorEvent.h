//
//  MouseEvent.h
//  TeslaEngine
//
//  Created by Eric Muxagata on 3/11/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//

#ifndef TeslaEngine_MouseEvent_h
#define TeslaEngine_MouseEvent_h


namespace tesla {

enum class MouseState {
    MOVED, ENTERED, EXITED
};

class MouseCursorEvent {
public:
    double x;
    double y;
    MouseState state;
    
    ~MouseCursorEvent(){};
};


};


#endif
