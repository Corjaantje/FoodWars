//
// Created by bryanvanlierop on 12/13/2018.
//

#include "../../../Headers/GameECS/Events/TurnSwitchedEvent.h"

TurnSwitchedEvent::TurnSwitchedEvent(int playerTurn) : _playerTurn{playerTurn} {}
TurnSwitchedEvent::~TurnSwitchedEvent() = default;

int TurnSwitchedEvent::getPlayerTurn() const {
    return _playerTurn;
}