//
// Created by svanr on 10/4/2018.
//

#ifndef PROJECT_SWA_IOBSERVER_H
#define PROJECT_SWA_IOBSERVER_H

#include <iostream>
#include "../Events/IEvent.h"

class IObserver{
public:
    IObserver() {

    }
    virtual ~IObserver() = 0;
    virtual void update(IEvent keyEvent) = 0; // update for observers that contains the pressed key
};

#endif //PROJECT_SWA_IOBSERVER_H
