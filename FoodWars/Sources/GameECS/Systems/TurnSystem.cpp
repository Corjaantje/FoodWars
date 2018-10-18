//
// Created by pietb on 11-Oct-18.
//

#include "../../../Headers/GameECS/Systems/TurnSystem.h"

//TurnSystem::TurnSystem() {
////    _turnComponents = new std::map<int, std::shared_ptr<TurnComponent>>{};
//    setTurnTime(30);
//}

TurnSystem::TurnSystem(EntityManager* entityManager): _entityManager(entityManager){
//    _turnComponents = new std::map<int, std::shared_ptr<TurnComponent>>{};
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

void TurnSystem::getRelevantEntities() {
    _turnComponents = _entityManager->getAllEntitiesWithComponent<TurnComponent>();
    _currentTurn = 0;
    _turnOrder.clear();
    for (auto const& x : _turnComponents)
    {
        _turnOrder.push_back(x.first);
    }
//    _activeTurn = *_turnComponents[_turnOrder[_currentTurn]];
}

//void TurnSystem::setRelevantEntities(std::vector<std::shared_ptr<TurnComponent>>* turns) {
void TurnSystem::setRelevantEntities(std::map<int, std::shared_ptr<TurnComponent>>* turns) {
//    _turnComponents->clear();
//    if (!_turnComponents->empty())
//    {
//        _turnComponents->clear();
//    }
//    _turnComponents = turns;
//    _turnComponents.assign(turns);
    _turnComponents = *turns;
//    _currentTurn = turns->begin()->first;
    _currentTurn = 0;
    _turnOrder.clear();
    for (auto const& x : *turns)
    {
        _turnOrder.push_back(x.first);
    }
}

void TurnSystem::setTurnTime(int turnTime) {
    _timePerTurn = turnTime;
//    _remainingTime = turnTime;
    if (!_turnOrder.empty())
    {
        _turnComponents[_turnOrder[_currentTurn]]->setRemainingTime(turnTime);
    }
}

// Lower remaining time of 'active' TurnComponent
// If remainingTime <= 0, end turn.
void TurnSystem::update(double deltaTime) {
//        _remainingTime -= deltaTime;
        _turnComponents[_turnOrder[_currentTurn]]->lowerRemainingTime(deltaTime);
//        _activeTurn.lowerRemainingTime(deltaTime);
//        _remainingTime = (_remainingTime > 0) ? _remainingTime - deltaTime : 30;
        if (_turnComponents[_turnOrder[_currentTurn]]->getRemainingTime() <= 0)
//        if (_remainingTime <= 0)
        {
//            _remainingTime = (float)_timePerTurn;
            // TODO
            // End turn of whomever's currently in charge
            endTurn();
        }
}

// End the 'active' TurnComponent's turn, start the next one.
void TurnSystem::endTurn() {
//    _turnComponents[_currentTurn]->switchTurn(false);
////    _currentTurn++;
//    _currentTurn = (_currentTurn < _turnComponents.size()) ? +1 : 0;
//    _turnComponents[_currentTurn]->switchTurn(true);
    // Change it to use a map, currently still thinking of a vector.
    // How to get size of "participants"?
    // Current participant? Next?
    _turnComponents[_turnOrder[_currentTurn]]->switchTurn(false);

    _currentTurn = (_currentTurn < _turnOrder.size()) ? +1 : 0;
//    _activeTurn = *_turnComponents[_turnOrder[_currentTurn]];

    _turnComponents[_turnOrder[_currentTurn]]->switchTurn(true);
    _turnComponents[_turnOrder[_currentTurn]]->setRemainingTime((float)_timePerTurn);
//    _turnComponents[_turnOrder[_currentTurn]]->switchTurn(false);
//    _currentTurn = (_currentTurn < _turnOrder.size()) ? +1 : 0;
//    _turnComponents[_turnOrder[_currentTurn]]->switchTurn(true);

}




