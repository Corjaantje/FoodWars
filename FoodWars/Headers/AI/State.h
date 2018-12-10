#include <utility>

#ifndef PROJECT_SWA_STATE_H
#define PROJECT_SWA_STATE_H

#include "../GameECS/Components/TurnComponent.h"
#include "../GameECS/Components/MoveComponent.h"
#include "../GameECS/Components/JumpComponent.h"
#include "../GameECS/Components/PlayerComponent.h"
#include "../GameECS/Entities/EntityManager.h"
#include "../../../TonicEngine/Headers/Audio/AudioFacade.h"
#include "../GameECS/Components/Collider/BoxCollider.h"
#include "../GameECS/Events/CollisionEvent.h"
#include "../GameECS/Events/CollisionEventHandler.h"

class AISystem;
class AIComponent;

class State {
protected:
    int _entityId;
    EntityManager* _entityManager;
    TurnComponent* _turnComponent;
    PositionComponent* _positionComponent;
    BoxCollider* _boxCollider;
    MoveComponent* _moveComponent;
    AIComponent* _aiComponent;

    std::shared_ptr<AudioFacade> _audioFacade;
    AISystem* _context;

    void jump(){
        auto turnComponent = _entityManager->getComponentFromEntity<TurnComponent>(_entityId);

        // kan ik springen?

        // nee: schiet

        if(!_entityManager->getComponentFromEntity<JumpComponent>(_entityId)) {
            _entityManager->addComponentToEntity<JumpComponent>(_entityId);
            turnComponent->lowerEnergy(5);
            //_audioFacade->playEffect("jump");
        }
    }

    int getDistanceToEnemy(int entityId) {
        for(const auto &iterator : _entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
            return calculateDistance(entityId, iterator.first);
        }
        // Player not found
        return 0;
    }

    // Calculates the manhattan distance between the centers two entities
    int calculateDistance(int entityOne, int entityTwo) {
        auto positionComponentOne = _entityManager->getComponentFromEntity<PositionComponent>(entityOne);
        auto positionComponentTwo = _entityManager->getComponentFromEntity<PositionComponent>(entityTwo);

        auto boxColliderOne = _entityManager->getComponentFromEntity<BoxCollider>(entityOne);
        auto boxColliderTwo = _entityManager->getComponentFromEntity<BoxCollider>(entityTwo);

        return abs((positionComponentOne->X + boxColliderOne->width) - (positionComponentTwo->X + boxColliderTwo->width)) + abs((positionComponentOne->Y + boxColliderOne->height) - (positionComponentTwo->Y + boxColliderTwo->height));
    }

public:
    State(EntityManager& entityManager, int entityId, AISystem& context) : _entityManager(&entityManager),
                            _entityId(entityId),
                            _context(&context),
                            _positionComponent {_entityManager->getComponentFromEntity<PositionComponent>(_entityId)},
                            _turnComponent{_entityManager->getComponentFromEntity<TurnComponent>(_entityId) },
                            _boxCollider { _entityManager->getComponentFromEntity<BoxCollider>(_entityId)},
                            _moveComponent {_entityManager->getComponentFromEntity<MoveComponent>(_entityId)} ,
                            _aiComponent { _entityManager->getComponentFromEntity<AIComponent>(_entityId)} {

    }

    virtual ~State() = default;
    //this will execute when the state is entered
    virtual void enter() = 0;
    //this is called by the update function each update step
    virtual void execute(double dt) = 0;
    //this will execute when the state is exited
    virtual void exit() = 0;
    //void update(double dt) override;
};

#endif //PROJECT_SWA_STATE_H