#include "../../Headers/Input/WindowClosedObserver.h"

WindowClosedObserver::~WindowClosedObserver() = default;

bool WindowClosedObserver::isWindowClosed() const {
    return _isClosed;
}

void WindowClosedObserver::update(WindowEvent& event) {
    if (event.GetWindowEventType() == WindowEventType::Quit) {
        _isClosed = true;
    }
}

WindowClosedObserver::WindowClosedObserver(): IObserver() {
}