//
// Created by svanr on 10/8/2018.
//

#ifndef PROJECT_SWA_WINDOWEVENT_H
#define PROJECT_SWA_WINDOWEVENT_H

#include "IEvent.h"

enum class WindowEventType {
    Quit,
    Minimize,
    Maximize,
    Resize
};

class WindowEvent: public IEvent {
private:
    WindowEventType _eventType;
public:
    WindowEvent();
    WindowEventType GetWindowEventType();
};

#endif //PROJECT_SWA_WINDOWEVENT_H
