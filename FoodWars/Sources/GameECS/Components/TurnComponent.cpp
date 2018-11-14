//
// Created by pietb on 15-Oct-18.
//

#include "../../../Headers/GameECS/Components/TurnComponent.h"

// Pure default initialization
TurnComponent::TurnComponent() {
    //TODO: discuss a default values.
    _energy = 100;
    _remainingTime = 0;
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

std::vector<std::string> TurnComponent::serialize() {
    std::vector<std::string> data;
    data.push_back(std::to_string(_energy));
    data.push_back(std::to_string(_myTurn));


    return data;
}

void TurnComponent::setEnergy(int energy) {
    _energy = energy;
    if (_energy > _maxEnergy) {_energy = _maxEnergy;}
}

void TurnComponent::setMaxEnergy(int energy) {
    _maxEnergy = energy;
}





