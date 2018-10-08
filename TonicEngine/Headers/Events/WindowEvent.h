//
// Created by svanr on 10/8/2018.
//

#ifndef PROJECT_SWA_WINDOWEVENT_H
#define PROJECT_SWA_WINDOWEVENT_H

#include "IEvent.h"

class WindowEvent: public IEvent {
public:
    enum{minimize, maximize, close};
};

#endif //PROJECT_SWA_WINDOWEVENT_H
