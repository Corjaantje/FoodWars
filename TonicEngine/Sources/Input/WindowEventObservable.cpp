#include "../../Headers/Input/WindowEventObservable.h"

WindowEventObservable::WindowEventObservable() {
}

WindowEventObservable::~WindowEventObservable() {
}

void WindowEventObservable::closeWindow() {
 _closed = true;
}