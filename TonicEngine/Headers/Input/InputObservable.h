//
// Created by svanr on 10/1/2018.
//

#include <vector>
#include <SDL2/SDL_events.h>
#include "IObservable.h"
#include <memory>
#include <map>
#include "../../Headers/Events/KeyEvent.h"

#ifndef PROJECT_SWA_INPUTOBSERVABLE_H
#define PROJECT_SWA_INPUTOBSERVABLE_H

class InputObservable: public IObservable {
private:
    std::vector<IObserver> _observerList;
    std::map<SDL_Event, IEvent> *_eventMap;
    std::map<IEvent, std::vector<IObserver>> *_observerMap = nullptr;
    KeyEvent *_keyEvent;

    void init();
    void notify(SDL_Event event) override;
    IEvent getEvent(SDL_Event eventName);
public:
    InputObservable();
    ~InputObservable();

    void registerObserver(IObserver& iObserver) override;

    void pollEvents();
};

#endif //PROJECT_SWA_INPUTOBSERVABLE_H