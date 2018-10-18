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
public:
    KeyEventObservable();
    ~KeyEventObservable() override;

};

#endif //PROJECT_SWA_KEYEVENTOBSERVABLE_H
