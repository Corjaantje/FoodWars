#include <utility>
#include "../../Headers/StateMachine/GameScreen.h"
#include "../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../../Headers/GameECS/Systems/CollisionSystem.h"
#include "../../Headers/GameECS/Systems/JumpSystem.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../Headers/StateMachine/PauseScreen.h"
#include "../../Headers/GameECS/Systems/DamageableSystem.h"


GameScreen::GameScreen(const std::shared_ptr<ScreenStateManager>& context,
                        EntityManager entityManager) : IScreen(context),
                            _entityManager(std::make_shared<EntityManager>(entityManager))
{
    _inputFacade->getKeyEventObservable()->registerKeyEventObserver(this);
    CollisionSystem* collisionSystem = new CollisionSystem{ _entityManager };
    _systems.push_back(new JumpSystem { _entityManager, _inputFacade, *collisionSystem } );
    _systems.push_back(new MoveSystem { _entityManager, _inputFacade, *collisionSystem });
    _systems.push_back(new GravitySystem { _entityManager, *collisionSystem });

    TurnSystem* turnSystem = new TurnSystem {_entityManager};
    _systems.push_back(turnSystem);
    shootSystem = new ShootSystem(_entityManager, visualFacade, _inputFacade);
    _systems.push_back(shootSystem);
    _systems.push_back(new DamageableSystem { _entityManager, *collisionSystem});
    _systems.push_back(collisionSystem);

    drawSystem = new DrawSystem {_entityManager, visualFacade, _inputFacade};
    _systems.push_back(drawSystem);

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

        if (event->getKey() == KEY::KEY_G){
            shootSystem->toggleShooting();
        }
        //Toggle Framerate
        if(event->getKey() == KEY::KEY_F){
            drawSystem->toggleFpsCounter();
        }
    }
}

GameScreen::~GameScreen() {
    for (auto const &iterator : _systems) {
        delete iterator;
    }
};

void GameScreen::update(double deltaTime) {
    audioFacade->playMusic("wildwest");
    _inputFacade->pollEvents();
    for(auto const &iterator : _systems){
        iterator->update(deltaTime * _context->getTimeModifier());
    }
}