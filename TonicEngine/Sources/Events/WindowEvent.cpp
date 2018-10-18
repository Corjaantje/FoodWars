#include "../../Headers/Events/WindowEvent.h"

WindowEvent::WindowEvent(int width, int height, WindowEventType windowEventType) : _width(width), _height(height), _eventType(windowEventType) {
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