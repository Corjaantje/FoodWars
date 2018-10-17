#include "../../Headers/Events/MouseEvent.h"

MouseEvent::MouseEvent(int x, int y) : _xPos(x), _yPos(y) {

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