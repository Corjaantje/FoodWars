//
// Created by svanr on 10/1/2018.
//

#include <vector>
#include <SDL2/SDL_events.h>
#include "IObservable.h"
#include <memory>

#ifndef PROJECT_SWA_INPUTOBSERVABLE_H
#define PROJECT_SWA_INPUTOBSERVABLE_H

class InputObservable: public IObservable {
private:
    std::vector<IObserver*> _observerList;
public:
    InputObservable();
    ~InputObservable();

    void registerObserver(IObserver& iObserver) override;
    void notify(std::string key) override;
    void pollEvents();
};

#endif //PROJECT_SWA_INPUTOBSERVABLE_H