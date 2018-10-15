//
// Created by pietb on 15-Oct-18.
//

#include "../../../Headers/GameECS/Components/TurnComponent.h"

TurnComponent::TurnComponent() {

}

TurnComponent::TurnComponent(int energy): _energy(energy) {

}

TurnComponent::TurnComponent(int energy, bool myTurn): _energy(energy), _myTurn(myTurn) {

}

TurnComponent::~TurnComponent() {

}

void TurnComponent::switchTurn(bool change) {
    _myTurn = change;
}


