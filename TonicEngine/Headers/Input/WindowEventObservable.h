#ifndef PROJECT_SWA_WINDOWEVENTOBSERVABLE_H
#define PROJECT_SWA_WINDOWEVENTOBSERVABLE_H

#include "../Events/WindowEvent.h"
#include "IObservable.h"

class WindowEventObservable : public IObservable<WindowEvent> {
private:
    bool _closed = false;
public:
    WindowEventObservable();
    ~WindowEventObservable() override;
    void closeWindow();
    inline bool isClosed() const { return _closed; };
};

#endif //PROJECT_SWA_WINDOWEVENTOBSERVABLE_H
