#ifndef PROJECT_SWA_WINDOWCLOSEDOBSERVER_H
#define PROJECT_SWA_WINDOWCLOSEDOBSERVER_H

#include "../Events/WindowEvent.h"
#include "IObserver.h"

class WindowClosedObserver : public IObserver<WindowEvent> {
private:
    bool _isClosed = false;
public:
    WindowClosedObserver();
    ~WindowClosedObserver();
    void update(WindowEvent& event);
    bool isWindowClosed() const;
};

#endif //PROJECT_SWA_WINDOWCLOSEDOBSERVER_H
