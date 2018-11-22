//
// Created by svanr on 10/4/2018.
//

#ifndef PROJECT_SWA_IOBSERVABLE_H
#define PROJECT_SWA_IOBSERVABLE_H

#include "memory"
#include <iostream>
#include <SDL2/SDL_events.h>
#include "../Events/IEvent.h"
#include "IObserver.h"
#include "../Events/KeyEvent.h"
#include <algorithm>

template <typename T>
class IObservable {
private:
    std::vector<IObserver<T>*> _observers;
public:
    IObservable() {

    }

    virtual ~IObservable(){

    }

    void registerObserver(IObserver<T>* iObserver) {
        _observers.push_back(iObserver);
    }

    void unregisterObserver(IObserver<T>* iObserver) {
        _observers.erase(std::remove(_observers.begin(), _observers.end(), iObserver), _observers.end());
    }

    void notify(std::shared_ptr<T> event) const {
        for(auto& observer: _observers){
            observer->update(event);
        }
    }
};

#endif //PROJECT_SWA_IOBSERVABLE_H
