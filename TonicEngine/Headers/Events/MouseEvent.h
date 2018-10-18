#ifndef PROJECT_SWA_MOUSEEVENT_H
#define PROJECT_SWA_MOUSEEVENT_H

#include "IEvent.h"

enum class MouseEventType {
    Down,
    Up
};

class MouseEvent: public IEvent {
private:
    int _xPos;
    int _yPos;
    MouseEventType _eventType;
public:
    MouseEvent(int x, int y);
    int getXPosition() const;
    int getYPosition() const;
    MouseEventType getMouseEventType();
};

#endif //PROJECT_SWA_MOUSEEVENT_H
