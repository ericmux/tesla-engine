//
//  IListener.h
//  TeslaEngine
//
//  Created by Eric Muxagata on 3/11/15.
//  Copyright (c) 2015 Eric Muxagata. All rights reserved.
//

#ifndef TeslaEngine_IListener_h
#define TeslaEngine_IListener_h

#include "IEvent.h"

namespace tesla {


template <typename T>
class IListener {
public:
    virtual ~IListener(){};
    virtual bool handleInput(T event) = 0;

};


};


#endif
