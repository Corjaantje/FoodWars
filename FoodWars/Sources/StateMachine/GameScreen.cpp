#include <utility>

#include <utility>
#include "../../Headers/StateMachine/GameScreen.h"
#include "../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../Headers/GameECS/Components/TurnComponent.h"
#include "../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../Headers/GameECS/Components/GravityComponent.h"
#include "../../Headers/GameECS/Components/MoveComponent.h"
#include "../../Headers/GameECS/Systems/CollisionSystem.h"
#include "../../Headers/GameECS/Systems/JumpSystem.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/StateMachine/PauseScreen.h"
#include "../../Headers/GameECS/Systems/AnimationSystem.h"
#include "../../Headers/GameECS/Components/AnimationComponent.h"

GameScreen::GameScreen(const std::shared_ptr<ScreenStateManager>& context, EntityManager entityManager) : IScreen(context), _entityManager(std::make_shared<EntityManager>(entityManager))
{
    _audioFacade = _context->getFacade<AudioFacade>();
    _visualFacade = _context->getFacade<VisualFacade>();
    _inputFacade->getKeyEventObservable()->registerKeyEventObserver(this);
    CollisionSystem* collisionSystem = new CollisionSystem{ _entityManager };
    _systems.push_back(new JumpSystem { _entityManager, _inputFacade, _audioFacade, *collisionSystem } );
    _systems.push_back(new MoveSystem { _entityManager, _inputFacade, *collisionSystem });
    _systems.push_back(collisionSystem);
    _systems.push_back(new GravitySystem { _entityManager, *collisionSystem });
    _systems.push_back(new AnimationSystem(_entityManager));
    _systems.push_back(new DrawSystem {_entityManager, visualFacade});
    _systems.push_back(new TurnSystem {_entityManager});
}

void GameScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE && event->getKeyEventType() == KeyEventType::Down) {
        _context->setActiveScreen<PauseScreen>();
    }
}

GameScreen::~GameScreen() {
    for (auto const &iterator : _systems) {
        delete iterator;
    }
};

void GameScreen::update(double deltaTime) {
    _audioFacade->playMusic("nature");
    _inputFacade->pollEvents();
    for (auto const &iterator : _systems) {
        iterator->update(deltaTime);
    }
}