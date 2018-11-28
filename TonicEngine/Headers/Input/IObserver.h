//
// Created by svanr on 10/4/2018.
//

#ifndef PROJECT_SWA_IOBSERVER_H
#define PROJECT_SWA_IOBSERVER_H

#include "memory"
#include <iostream>
#include "../Events/IEvent.h"

template <typename T>
class IObserver{
public:
    IObserver() {

    }
    ~IObserver() {

    }
    virtual void update(const T& event) = 0;
};

#endif //PROJECT_SWA_IOBSERVER_H