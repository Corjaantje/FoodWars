//
// Created by svanr on 10/15/2018.
//

#ifndef PROJECT_SWA_MOUSEEVENTOBSERVABLE_H
#define PROJECT_SWA_MOUSEEVENTOBSERVABLE_H

#include "../Events/MouseEvent.h"
#include "IObservable.h"

class MouseEventObservable : public IObservable<MouseEvent> {
private:
public:
    MouseEventObservable();
    ~MouseEventObservable() override;
};

#endif //PROJECT_SWA_MOUSEEVENTOBSERVABLE_H
