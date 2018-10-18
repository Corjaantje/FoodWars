#ifndef PROJECT_SWA_WINDOWEVENTOBSERVABLE_H
#define PROJECT_SWA_WINDOWEVENTOBSERVABLE_H

#include "../Events/WindowEvent.h"
#include "IObservable.h"

class WindowEventObservable : public IObservable<WindowEvent> {
public:
    WindowEventObservable();
    ~WindowEventObservable() override;
};

#endif //PROJECT_SWA_WINDOWEVENTOBSERVABLE_H
