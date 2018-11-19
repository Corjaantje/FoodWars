//
// Created by pietb on 11-Oct-18.
//

#include "../../../Headers/GameECS/Systems/TurnSystem.h"

//TurnSystem::TurnSystem() {
//    setTurnTime(_defaultTimePerTurn);
//}

TurnSystem::TurnSystem(std::shared_ptr<EntityManager> entityManager){
    _entityManager = entityManager;
    _timePerTurn = _defaultTimePerTurn;
}

TurnSystem::~TurnSystem() {

}

// Lower remaining time of 'active' TurnComponent
// If remainingTime <= 0, end turn.
void TurnSystem::update(double deltaTime) {
    std::map<int, std::shared_ptr<TurnComponent>> turnComponents = _entityManager->getAllEntitiesWithComponent<TurnComponent>();
    for(const auto &iterator: turnComponents) {
        if(iterator.second->isMyTurn()) {
            iterator.second->lowerRemainingTime(deltaTime);
            if(iterator.second->getRemainingTime() <= 0 || iterator.second->getEnergy() <= 0) {
                iterator.second->switchTurn(false);
                for(const auto& it2: turnComponents) {
                    if(it2.first != iterator.first) {
                        it2.second->switchTurn(true);
                        it2.second->setRemainingTime((float) _timePerTurn);
                        break;
                    }
                }
            }
            break;
        }
    }
}



