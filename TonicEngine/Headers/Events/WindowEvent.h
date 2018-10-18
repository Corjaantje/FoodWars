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
    int _width;
    int _height;
public:
    WindowEvent(int width, int height);
    int getWidth() const;
    int getHeight() const;
    WindowEventType GetWindowEventType();
};

#endif //PROJECT_SWA_WINDOWEVENT_H
