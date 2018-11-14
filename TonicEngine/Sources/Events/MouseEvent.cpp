#include "../../Headers/Events/MouseEvent.h"

MouseEvent::MouseEvent(int x, int y, MouseEventType eventType, MouseClickType clickType) : _xPos(x), _yPos(y), _eventType(eventType), _clickType(clickType) {

}

int MouseEvent::getXPosition() const {
    return _xPos;
}

int MouseEvent::getYPosition() const {
    return _yPos;
}

MouseEventType MouseEvent::getMouseEventType() {
    return _eventType;
}

MouseClickType MouseEvent::getMouseClickType() {
    return _clickType;
}