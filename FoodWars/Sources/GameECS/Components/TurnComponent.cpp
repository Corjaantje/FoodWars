//
// Created by pietb on 15-Oct-18.
//

#include "../../../Headers/GameECS/Components/TurnComponent.h"

// Pure default initialization
TurnComponent::TurnComponent() {
    //TODO: discuss a default values.
    _energy = 100;
}

// Alternative amount of energy
TurnComponent::TurnComponent(int energy): _energy(energy) {

}

TurnComponent::TurnComponent(int energy, bool myTurn): _energy(energy), _myTurn(myTurn) {

}

TurnComponent::~TurnComponent() {

}

void TurnComponent::switchTurn(bool change) {
    _myTurn = change;
}

void TurnComponent::setRemainingTime(double t) {
    _remainingTime = t;
}

void TurnComponent::lowerRemainingTime(double t) {
    _remainingTime -= t;
}

double TurnComponent::getRemainingTime() const {
    return _remainingTime;
}

bool TurnComponent::isMyTurn() const {
    return _myTurn;
}





