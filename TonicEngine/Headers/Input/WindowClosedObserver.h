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
    void update(std::shared_ptr<WindowEvent> event);
    bool isWindowClosed() const;
};

#endif //PROJECT_SWA_WINDOWCLOSEDOBSERVER_H
