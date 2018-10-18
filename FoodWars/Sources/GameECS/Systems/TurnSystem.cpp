//
// Created by pietb on 11-Oct-18.
//

#include "../../../Headers/GameECS/Systems/TurnSystem.h"

//TurnSystem::TurnSystem() {
//    setTurnTime(_defaultTimePerTurn);
//}

TurnSystem::TurnSystem(std::shared_ptr<EntityManager> entityManager){
    _entityManager = entityManager;
    getRelevantEntities();
    setTurnTime(_defaultTimePerTurn);
}

TurnSystem::~TurnSystem() {

}

void TurnSystem::getRelevantEntities() {
    _turnComponents = _entityManager->getAllEntitiesWithComponent<TurnComponent>();
    _currentTurn = 0;
    _turnOrder.clear();
    for (auto const& x : _turnComponents)
    {
        _turnOrder.push_back(x.first);
    }
    setTurnTime(_defaultTimePerTurn);
}

// May be relevant for loading a game in progress.
void TurnSystem::setRelevantEntities(std::map<int, std::shared_ptr<TurnComponent>>* turns) {
    _turnComponents = *turns;
    _currentTurn = 0;
    _turnOrder.clear();
    for (auto const& x : *turns)
    {
        _turnOrder.push_back(x.first);
    }
    setTurnTime(_defaultTimePerTurn);
}

void TurnSystem::setTurnTime(int turnTime) {
    _timePerTurn = turnTime;
//    if (!_turnOrder.empty())
//    {
//        _turnComponents[_turnOrder[_currentTurn]]->setRemainingTime(turnTime);
//    }
}

// Lower remaining time of 'active' TurnComponent
// If remainingTime <= 0, end turn.
void TurnSystem::update(double deltaTime) {
        _turnComponents[_turnOrder[_currentTurn]]->lowerRemainingTime(deltaTime);
        if (_turnComponents[_turnOrder[_currentTurn]]->getRemainingTime() <= 0 || _turnComponents[_turnOrder[_currentTurn]]->getmyEnergy() <= 0)
        {
            endTurn();
        }
}

// End the 'active' TurnComponent's turn, start the next one.
void TurnSystem::endTurn() {
    _turnComponents[_turnOrder[_currentTurn]]->switchTurn(false);

    _currentTurn = (_currentTurn < _turnOrder.size()-1) ? +1 : 0;

    _turnComponents[_turnOrder[_currentTurn]]->switchTurn(true);
    _turnComponents[_turnOrder[_currentTurn]]->setRemainingTime((float)_timePerTurn);
    _turnComponents[_turnOrder[_currentTurn]]->resetEnergyToMax();

}






