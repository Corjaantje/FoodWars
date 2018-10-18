#ifndef PROJECT_SWA_PRINTWINDOWOBSERVER_H
#define PROJECT_SWA_PRINTWINDOWOBSERVER_H

#include "../Events/WindowEvent.h"
#include "IObserver.h"

class PrintWindowObserver : public IObserver<WindowEvent> {
private:
    ~PrintWindowObserver();
public:
    PrintWindowObserver();
    void update(std::shared_ptr<WindowEvent> event);
};

#endif //PROJECT_SWA_PRINTWINDOWOBSERVER_H
