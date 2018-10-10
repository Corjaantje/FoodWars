#ifndef PROJECT_SWA_DRAWSYSTEM_H
#define PROJECT_SWA_DRAWSYSTEM_H


#include "IBaseSystem.h"

class DrawSystem: public IBaseSystem {
    DrawSystem() : IBaseSystem(_entityManager){

    };

    ~DrawSystem();

    virtual void Update(double dt) override {

    }
};


#endif //PROJECT_SWA_DRAWSYSTEM_H
