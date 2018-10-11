//
// Created by Corne on 11-Oct-18.
//

#ifndef PROJECT_SWA_ENTITYWITHCOMP_H
#define PROJECT_SWA_ENTITYWITHCOMP_H


#include "../Components/Component.h"

class EntityWithComp {
public:
    int _id;
    Component _component;
    EntityWithComp(int entityId, Component component);
};


#endif //PROJECT_SWA_ENTITYWITHCOMP_H
