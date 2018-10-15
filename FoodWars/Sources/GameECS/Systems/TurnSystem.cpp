//
// Created by pietb on 11-Oct-18.
//

#include "../../../Headers/GameECS/Systems/TurnSystem.h"

TurnSystem::TurnSystem() {
    _turnComponents = new std::vector<std::shared_ptr<TurnComponent>>{};
    setTurnTime(30);
}

TurnSystem::TurnSystem(EntityManager* entityManager): _entityManager(entityManager){
    _turnComponents = new std::vector<std::shared_ptr<TurnComponent>>{};
    setTurnTime(30);
}

//TurnSystem::TurnSystem(EntityManager* entityManager, int turnTime): _entityManager(entityManager), _timePerTurn(turnTime) {
//    //:_timePerTurn(turnTime*60)
//}

TurnSystem::~TurnSystem() {

}

//int TurnSystem::timePassed() {
//    _timePerTurn--;
//    return 0;
//}

void TurnSystem::setRelevantEntities(std::vector<std::shared_ptr<TurnComponent>>* turns) {
//    _turnComponents->clear();
//    if (!_turnComponents->empty())
//    {
//        _turnComponents->clear();
//    }
//    _turnComponents = turns;
//    _turnComponents.assign(turns);
    _turnComponents = turns;
}

void TurnSystem::setTurnTime(int turnTime) {
    _timePerTurn = turnTime;
    _remainingTime = turnTime;
}

void TurnSystem::update(double deltaTime) {
        _remainingTime -= deltaTime;
//        _remainingTime = (_remainingTime > 0) ? _remainingTime - deltaTime : 30;
        if (_remainingTime <= 0)
        {
            _remainingTime = (float)_timePerTurn;
            // TODO
            // End turn of whomever's currently in charge
            endTurn();
        }
}

void TurnSystem::endTurn() {
    _turnComponents[_currentTurn][0]->switchTurn(false);
//    _currentTurn++;
    _currentTurn = (_currentTurn < _turnComponents->size()) ? +1 : 0;
    _turnComponents[_currentTurn][0]->switchTurn(true);
}




