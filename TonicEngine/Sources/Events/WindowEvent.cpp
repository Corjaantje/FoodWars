#include "../../Headers/Events/WindowEvent.h"

WindowEvent::WindowEvent(int width, int height) : _width(width), _height(height) {
}

int WindowEvent::getWidth() const {
    return _width;
}

int WindowEvent::getHeight() const {
    return _height;
}

WindowEventType WindowEvent::GetWindowEventType() {
  return _eventType;
}