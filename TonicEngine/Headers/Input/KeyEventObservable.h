//
// Created by Lucas on 15/10/2018.
//

#ifndef PROJECT_SWA_KEYEVENTOBSERVABLE_H
#define PROJECT_SWA_KEYEVENTOBSERVABLE_H

#include <map>
#include "../Events/KeyEvent.h"
#include "IObservable.h"

class KeyEventObservable : public IObservable<KeyEvent> {
private:
    std::map<SDL_Keycode, KEY> _keycodeMap;
    std::map<KEY, bool> _pressedKeys;
public:
    KeyEventObservable();
    ~KeyEventObservable() override;
    void update() const;

};

#endif //PROJECT_SWA_KEYEVENTOBSERVABLE_H
