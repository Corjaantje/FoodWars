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
    std::vector<IObserver*> _observerList;
    std::map<std::string, IEvent> *_eventMap = nullptr;
    KeyEvent* _keyEvent;

    void init();
    void notify(IEvent keyEvent) override;
    IEvent getEvent(std::string eventName);
public:
    InputObservable();
    ~InputObservable();

    void registerObserver(IObserver& iObserver) override;

    void pollEvents();
};

#endif //PROJECT_SWA_INPUTOBSERVABLE_H