#include <utility>

#include <utility>
#include "../../Headers/StateMachine/GameScreen.h"
#include "../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../../Headers/GameECS/Components/TurnComponent.h"
#include "../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../Headers/GameECS/Components/GravityComponent.h"
#include "../../Headers/GameECS/Components/MoveComponent.h"
#include "../../Headers/GameECS/Systems/CollisionSystem.h"
#include "../../Headers/GameECS/Systems/JumpSystem.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../Headers/StateMachine/PauseScreen.h"
#include "../../Headers/GameECS/Systems/AnimationSystem.h"
#include "../../Headers/GameECS/Components/AnimationComponent.h"
#include "../../Headers/StateMachine/DrawTransitionScreen.h"
#include "../../Headers/StateMachine/WinTransitionScreen.h"
#include "../../Headers/StateMachine/LoseTransitionScreen.h"

GameScreen::GameScreen(const std::shared_ptr<ScreenStateManager>& context, EntityManager entityManager) : IScreen(context), _entityManager(std::make_shared<EntityManager>(entityManager))
{
    _audioFacade = _context->getFacade<AudioFacade>();
    _visualFacade = _context->getFacade<VisualFacade>();
    _inputFacade->getKeyEventObservable()->registerKeyEventObserver(this);
    _animationManager = new AnimationManager{};
    CollisionSystem* collisionSystem = new CollisionSystem{ _entityManager };
    _systems.push_back(new JumpSystem { _entityManager, _inputFacade, _audioFacade, *collisionSystem} );
    _systems.push_back(new MoveSystem{ _entityManager, _inputFacade, *collisionSystem});
    _systems.push_back(collisionSystem);
    _systems.push_back(new GravitySystem { _entityManager, *collisionSystem });
    _systems.push_back(new AnimationSystem(_entityManager, _animationManager));
    _systems.push_back(new DrawSystem {_entityManager, visualFacade});
    _systems.push_back(new TurnSystem {_entityManager});
}

void GameScreen::update(std::shared_ptr<KeyEvent> event){
    if (event->getKeyEventType() == KeyEventType::Down) {
        if(event->getKey() == KEY::KEY_ESCAPE)
            _context->setActiveScreen<PauseScreen>();

        //Adjusting gamespeed
        if(event->getKey() == KEY::KEY_PAGEUP) {
            _context->setTimeModifier(2.50);
        }
        if(event->getKey() == KEY::KEY_PAGEDOWN) {
            _context->setTimeModifier(0.40);
        }
        if(event->getKey() == KEY::KEY_HOME) {
            _context->setTimeModifier(1);
        }

        //Toggle Framerate
        if(event->getKey() == KEY::KEY_F){
            drawSystem->toggleFpsCounter();
        }
    }
    /*if (event->getKey() == KEY::KEY_A)
    {
        _entityManager->getComponentFromEntity<DamageableComponent>(teamTwo[0])->LowerHealth(10);
    }*/
}

GameScreen::~GameScreen() {
    for (auto const &iterator : _systems) {
        delete iterator;
    }
    delete _animationManager;
};

void GameScreen::update(double deltaTime) {
    /*std::map<int, std::shared_ptr<TurnComponent>> _entitiesWithTurnComponent = _entityManager->getAllEntitiesWithComponent<TurnComponent>();
    if(_entitiesWithTurnComponent.size() == 1)
    {
        //set score
        if (_entitiesWithTurnComponent.count(teamOne[0]) > 0) {
            // Win
            //set score
            _context->setActiveScreen<WinTransitionScreen>();
            ((std::dynamic_pointer_cast<WinTransitionScreen>(_context->getCurrentState())->setScore(100)));

        }
        else {
            // Loss
            //set score
            _context->setActiveScreen<LoseTransitionScreen>();
            ((std::dynamic_pointer_cast<LoseTransitionScreen>(_context->getCurrentState())->setScore(-100)));
        }
    } else if(_entitiesWithTurnComponent.empty()) {
        // Draw
        //set score
        _context->setActiveScreen<DrawTransitionScreen>();
        ((std::dynamic_pointer_cast<DrawTransitionScreen>(_context->getCurrentState())->setScore(0)));
    }*/
    _audioFacade->playMusic("wildwest");
    _inputFacade->pollEvents();
    for(auto const &iterator : _systems){
        iterator->update(deltaTime * _context->getTimeModifier());
    }

}