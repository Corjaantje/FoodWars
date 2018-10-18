#ifndef PROJECT_SWA_PRINTMOUSEINPUTOBSERVER_H
#define PROJECT_SWA_PRINTMOUSEINPUTOBSERVER_H

#include "../Events/MouseEvent.h"
#include "IObserver.h"

class PrintMouseInputObserver: public IObserver<MouseEvent> {
private:
    ~PrintMouseInputObserver();
public:
    PrintMouseInputObserver();
    void update(std::shared_ptr<MouseEvent> event);
};

#endif //PROJECT_SWA_PRINTMOUSEINPUTOBSERVER_H
