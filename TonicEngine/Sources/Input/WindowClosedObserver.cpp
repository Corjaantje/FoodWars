#include "../../Headers/Input/WindowClosedObserver.h"

WindowClosedObserver::~WindowClosedObserver() = default;

bool WindowClosedObserver::isWindowClosed() {
    return _isClosed;
}

void WindowClosedObserver::update(std::shared_ptr<WindowEvent> event) {
    if (event->GetWindowEventType() == WindowEventType::Quit) {
        _isClosed = true;
    }
}

WindowClosedObserver::WindowClosedObserver(): IObserver() {
}