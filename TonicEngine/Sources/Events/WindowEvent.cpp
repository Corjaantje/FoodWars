#include "../../Headers/Events/WindowEvent.h"

WindowEvent::WindowEvent() {
}

WindowEventType WindowEvent::GetWindowEventType() {
  return _eventType;
}