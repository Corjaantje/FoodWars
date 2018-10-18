//
// Created by svanr on 10/8/2018.
//

#ifndef PROJECT_SWA_WINDOWEVENT_H
#define PROJECT_SWA_WINDOWEVENT_H

#include "IEvent.h"
#include <string>

enum class WindowEventType {
    Quit,
    Resize
};

class WindowEvent: public IEvent {
private:
    WindowEventType _eventType;
    int _width;
    int _height;
public:
    WindowEvent(int width, int height, WindowEventType windowEventType);
    int getWidth() const;
    int getHeight() const;
    bool quitRequest() const;
    WindowEventType GetWindowEventType();
};

#endif //PROJECT_SWA_WINDOWEVENT_H
