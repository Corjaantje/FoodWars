//
// Created by Lucas on 11/10/2018.
//

#include "../../Headers/StateMachine/ScreenPtr.h"

ScreenPtr::ScreenPtr(const IScreen *screen) {
    _screen = screen;
}

ScreenPtr::~ScreenPtr() {
    delete _screen;
}

void ScreenPtr::update(double deltaTime) const {
    _screen->update(deltaTime);
}

ScreenPtr::ScreenPtr(const ScreenPtr &other){ //copy constructor
    _screen = other._screen;
}

ScreenPtr& ScreenPtr::operator=(const ScreenPtr& other) {
    if(this != &other) {
        delete _screen;
        _screen = other._screen;
    }
    return *this;
}

ScreenPtr::ScreenPtr(ScreenPtr &&other) noexcept { //move constructor
    _screen = other._screen;
    other._screen = nullptr;
}

ScreenPtr& ScreenPtr::operator=(ScreenPtr &&other) noexcept {
    if(this != &other){
        delete _screen;
        _screen = other._screen;
        other._screen = nullptr;
    }
    return *this;
}