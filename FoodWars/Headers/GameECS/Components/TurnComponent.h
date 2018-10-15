//
// Created by pietb on 15-Oct-18.
//

#ifndef PROJECT_SWA_TURNCOMPONENT_H
#define PROJECT_SWA_TURNCOMPONENT_H

#include "Component.h"

class TurnComponent: public Component {
public:
    TurnComponent();
    TurnComponent(int energy, bool myTurn);
    ~TurnComponent();

private:
    int _energy;
    bool _myTurn = false;
};


#endif //PROJECT_SWA_TURNCOMPONENT_H
