#ifndef PROJECT_SWA_MOUSEEVENT_H
#define PROJECT_SWA_MOUSEEVENT_H

#include "IEvent.h"

enum class MouseEventType {
    Down,
    Up,
    Drag
};

enum class MouseClickType {
    Left,
    Right
};

class MouseEvent: public IEvent {
private:
    int _xPos;
    int _yPos;
    MouseEventType _eventType;
    MouseClickType  _clickType;
public:
    MouseEvent(int x, int y, MouseEventType eventType, MouseClickType clickType);
    int getXPosition() const;
    int getYPosition() const;
    MouseEventType getMouseEventType();
    MouseClickType getMouseClickType();
};

#endif //PROJECT_SWA_MOUSEEVENT_H
