//
// Created by Lucas on 15/10/2018.
//

#ifndef PROJECT_SWA_KEYEVENTOBSERVABLE_H
#define PROJECT_SWA_KEYEVENTOBSERVABLE_H

#include <map>
#include "../Events/KeyEvent.h"
#include "IObservable.h"

class KeyEventObservable : public IObservable<KeyEvent>, public IObservable<std::map<KEY, bool>> {
private:
    std::map<SDL_Keycode, KEY> _keycodeMap;
    std::map<KEY, bool> _pressedKeys;
public:
    KeyEventObservable();
    ~KeyEventObservable() override;
    void registerKeyEventObserver(IObserver<KeyEvent>* observer);
    void registerKeyPressedMapObserver(IObserver<std::map<KEY, bool>>* observer);
    void update();

};

#endif //PROJECT_SWA_KEYEVENTOBSERVABLE_H
