//
// Created by svanr on 10/8/2018.
//

#ifndef PROJECT_SWA_KEYEVENT_H
#define PROJECT_SWA_KEYEVENT_H

#include <iostream>
#include <vector>
#include "IEvent.h"
#include "../Input/IObserver.h"


class KeyEvent: public IEvent {
private:
    std::vector<IObserver*> _observerList;
    enum KEYS {KEY_W, KEY_A, KEY_S, KEY_D};
public:
    void registerObserver() override;
    void notify() override;
};

#endif //PROJECT_SWA_KEYEVENT_H
