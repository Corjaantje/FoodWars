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

GameScreen::GameScreen(const std::shared_ptr<ScreenStateManager> &context, EntityManager entityManager) : IScreen(context),
    _entityManager(std::make_shared<EntityManager>(entityManager)),
    _audioFacade(context->getFacade<AudioFacade>()),
    _visualFacade(context->getFacade<VisualFacade>()){
    _inputFacade->getKeyEventObservable()->registerKeyEventObserver(this);
    _inputFacade->setWindowResolutionCalculator(_context->getWindowResolutionCalculator());
    std::shared_ptr<CollisionSystem> collisionSystem = std::make_shared<CollisionSystem>(_entityManager);
    _systems.push_back(std::make_shared<JumpSystem>(_entityManager, _inputFacade, *collisionSystem));
    _systems.push_back(std::make_shared<MoveSystem>(_entityManager, _inputFacade, *collisionSystem));
    _systems.push_back(std::make_shared<GravitySystem>(_entityManager, *collisionSystem));
    _systems.push_back(collisionSystem);
    _systems.push_back(std::make_shared<DrawSystem>(_entityManager, _visualFacade));

    std::shared_ptr<TurnSystem> turnSystem = std::make_shared<TurnSystem>(_entityManager);
    _systems.push_back(turnSystem);
}

void GameScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE) {
        _context->setActiveScreen<PauseScreen>();
    }
}

GameScreen::~GameScreen() = default;

void GameScreen::update(double deltaTime) {
    _audioFacade->playMusic("wildwest");
    _inputFacade->pollEvents();
    for(auto const &iterator : _systems){
        iterator->update(deltaTime);
    }
}