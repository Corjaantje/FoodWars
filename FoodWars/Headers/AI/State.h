#include <utility>

#ifndef PROJECT_SWA_STATE_H
#define PROJECT_SWA_STATE_H

#include "../GameECS/Components/TurnComponent.h"
#include "../GameECS/Components/MoveComponent.h"
#include "../GameECS/Components/JumpComponent.h"
#include "../GameECS/Entities/EntityManager.h"
#include "../../../TonicEngine/Headers/Audio/AudioFacade.h"

class State {
protected:
    int _walkingEnergyCostPerSecond = 20;
    EntityManager* _entityManager;
    std::shared_ptr<AudioFacade> _audioFacade;
    int _entityId;


    void jump(){
        auto turnComponent = _entityManager->getComponentFromEntity<TurnComponent>(_entityId);
        if(!_entityManager->getComponentFromEntity<JumpComponent>(_entityId)) {
            _entityManager->addComponentToEntity<JumpComponent>(_entityId);
            turnComponent->lowerEnergy(5);
            _audioFacade->playEffect("jump");
        }
    }

    void walkLeft(MoveComponent& moveComponent, TurnComponent& turnComponent, double dt) {
        moveComponent.xVelocity = -100;
        turnComponent.lowerEnergy(_walkingEnergyCostPerSecond * dt);
    }

    void walkRight(MoveComponent& moveComponent, TurnComponent& turnComponent, double dt) {
        moveComponent.xVelocity = 100;
        turnComponent.lowerEnergy(_walkingEnergyCostPerSecond * dt);
    }
public:
    State(EntityManager* entityManager, std::shared_ptr<AudioFacade> audioFacade, int entityId) : _entityManager(entityManager), _audioFacade(std::move(audioFacade)), _entityId(entityId){
        
    }

    virtual ~State() = default;
    //this will execute when the state is entered
    virtual void enter() = 0;
    //this is called by the update function each update step
    virtual void execute(double dt) = 0;
    //this will execute when the state is exited
    virtual void exit() = 0;
};

#endif //PROJECT_SWA_STATE_H
