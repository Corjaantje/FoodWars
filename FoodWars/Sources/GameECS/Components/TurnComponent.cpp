//
// Created by pietb on 15-Oct-18.
//

#include "../../../Headers/GameECS/Components/TurnComponent.h"

TurnComponent::TurnComponent() {

}

TurnComponent::TurnComponent(int energy): _maxEnergy(energy) {

}

TurnComponent::TurnComponent(int energy, bool myTurn): _maxEnergy(energy), _myTurn(myTurn) {

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

void TurnComponent::resetEnergyToMax() {
    _currentEnergy = _maxEnergy;
}

double TurnComponent::getRemainingTime() const {
    return _remainingTime;
}

bool TurnComponent::getMyTurn() const {
    return _myTurn;
}

int TurnComponent::getmyEnergy() const {
    return _currentEnergy;
}






