//
// Created by svanr on 10/4/2018.
//

#ifndef PROJECT_SWA_IOBSERVER_H
#define PROJECT_SWA_IOBSERVER_H

#include <iostream>

class IObserver{
public:
    IObserver() {

    }
    virtual ~IObserver() = 0;
    virtual void update(std::string key) = 0;
};

#endif //PROJECT_SWA_IOBSERVER_H
