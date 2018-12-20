#include "../../../Headers/GameECS/Systems/TurnSystem.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeSprite.h"
#include "../../../Headers/GameECS/Components/PositionComponent.h"
#include "../../../Headers/GameECS/Components/AIComponent.h"

TurnSystem::TurnSystem(EntityManager &entityManager) : _entityManager(&entityManager), _defaultTimePerTurn(30),
                                                       _timePerTurn(_defaultTimePerTurn) {
}

TurnSystem::~TurnSystem() = default;

// Lower remaining time of 'active' TurnComponent
// If remainingTime <= 0, end turn.
void TurnSystem::update(double deltaTime) {
    std::map<int, TurnComponent *> turnComponents = _entityManager->getAllEntitiesWithComponent<TurnComponent>();
    int currentPlayerId = -1;
    for(const auto &iterator: turnComponents) {
        if(iterator.second->isMyTurn()) {
            currentPlayerId = iterator.first;
            iterator.second->lowerRemainingTime(deltaTime);
            if(iterator.second->getRemainingTime() <= 0) {
                iterator.second->setRemainingTime(0);
                iterator.second->setEnergy(0);
            }
            break;
        }
    }

    if(_currentHighlightEntityId != -1) {
        auto playerPos = _entityManager->getComponentFromEntity<PositionComponent>(currentPlayerId);
        auto arrowPos = _entityManager->getComponentFromEntity<PositionComponent>(_currentHighlightEntityId);
        arrowPos->X = playerPos->X;
        arrowPos->Y = playerPos->Y - 100;
        resetPlayerHighlight(deltaTime);
    }
}

void TurnSystem::switchTurn() {
    for (const auto &iterator: _entityManager->getAllEntitiesWithComponent<TurnComponent>()) {
        if (iterator.second->isMyTurn()) {
            if ((_entityManager->getComponentFromEntity<AIComponent>(iterator.first) &&
                 (iterator.second->getEnergy() <= 0.0 || iterator.second->getRemainingTime() <= 0))
                || !_entityManager->getComponentFromEntity<AIComponent>(iterator.first)) {
                iterator.second->switchTurn(false);
                iterator.second->setEnergy(100);
                for (const auto &iterator2: _entityManager->getAllEntitiesWithComponent<TurnComponent>()) {
                    if (iterator.first != iterator2.first) {
                        iterator2.second->switchTurn(true);
                        iterator2.second->setRemainingTime(30);
                        if (_currentHighlightEntityId != -1) {
                            resetPlayerHighlight(2.1);
                        }
                        createCurrentPlayerHighlight(iterator2.first);
                        TurnSwitchedEvent event = TurnSwitchedEvent{iterator2.first};
                        notify(event);
                    }
                }
                break;
            }
        }
    }
}

void TurnSystem::createCurrentPlayerHighlight(int entityID) {
    _currentHighlightEntityId = _entityManager->createEntity();
    auto *positionComp = _entityManager->getComponentFromEntity<PositionComponent>(entityID);
    if (positionComp != nullptr) {
        _entityManager->addComponentToEntity<PositionComponent>(_currentHighlightEntityId, positionComp->X, positionComp->Y - 100);
        _entityManager->addComponentToEntity<DrawableComponent>(_currentHighlightEntityId,
                                                                std::make_unique<ShapeSprite>(48, 72,
                                                                                              positionComp->X,
                                                                                              positionComp->Y - 100,
                                                                                              "HighlightArrow.png", 4));
    }
}

void TurnSystem::resetPlayerHighlight(double deltaTime) {
    _timePerUpdateHighlight += deltaTime;
    if(_timePerUpdateHighlight > 2.0){
        _timePerUpdateHighlight = 0;
        _entityManager->removeEntity(_currentHighlightEntityId);
        _currentHighlightEntityId = -1;
    }
}

void TurnSystem::resetCurrentTime() {
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<TurnComponent>()) {
        if (iterator.second->isMyTurn()) {
            iterator.second->setRemainingTime(30);
            break;
        }
    }
}

int TurnSystem::getCurrentPlayerID() const {
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<TurnComponent>()) {
        if (iterator.second->isMyTurn()) {
            return iterator.first;
        }
    }
}

void TurnSystem::resetCurrentEnergy() {
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<TurnComponent>()) {
        if (iterator.second->isMyTurn()) {
            iterator.second->setEnergy(100);
            break;
        }
    }
}

double TurnSystem::getCurrentPlayerEnergy() const {
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<TurnComponent>())
        if (iterator.second->isMyTurn()) return iterator.second->getEnergy();
}



