#include <cmath>
#include "../../../Headers/GameECS/Systems/AISystem.h"
#include "../../../Headers/AI/IdleState.h"
#include "../../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/ShapeSprite.h"
#include "../../../Headers/GameECS/Components/DamagingComponent.h"
#include "../../../Headers/GameECS/Components/GravityComponent.h"
#include "../../../Headers/GameECS/Components/DamageableComponent.h"

AISystem::AISystem(EntityManager &entityManager, AudioFacade& audioFacade, IObservable<CollisionEvent>& collisionEventObservable)
                                        : _entityManager(&entityManager), _collisionEventObservable(&collisionEventObservable), _audioFacade(&audioFacade){
    for(const auto iterator: _entityManager->getAllEntitiesWithComponent<AIComponent>()) {
        iterator.second->setCurrentState(std::make_unique<IdleState>(*_entityManager, iterator.first, *this));
    }
}

AISystem::~AISystem() = default;

void AISystem::update(double dt) {
    for(const auto &iterator: _entityManager->getAllEntitiesWithComponent<AIComponent>()) {
        iterator.second->update(dt);
    }
}

IObservable<CollisionEvent> &AISystem::getCollisionEventObservable() {
    return *_collisionEventObservable;
}

AudioFacade &AISystem::getAudioFacade() const {
    return *_audioFacade;
}
