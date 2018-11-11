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

GameScreen::GameScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context),
                                                                      _entityManager(std::make_shared<EntityManager>()) {
    _inputFacade->getKeyEventObservable()->registerKeyEventObserver(this);
    CollisionSystem* collisionSystem = new CollisionSystem{ _entityManager };
    _systems.push_back(new JumpSystem { _entityManager, _inputFacade, *collisionSystem } );
    _systems.push_back(new MoveSystem { _entityManager, _inputFacade, *collisionSystem });
    _systems.push_back(collisionSystem);
    _systems.push_back(new GravitySystem { _entityManager, *collisionSystem });
    _systems.push_back(new DrawSystem {_entityManager, visualFacade});
    int player = _entityManager->createEntity();

    DrawableComponent *drawableComponent = new DrawableComponent;
    drawableComponent->shape = std::make_unique<ShapeSprite>(ShapeSprite({32, 48, 0, 0, "PlayerW_R0.png"}));
    _entityManager->addComponentToEntity(player, drawableComponent);
    _entityManager->addComponentToEntity(player, new BoxCollider(32, 48));
    TurnComponent *turnComponent = new TurnComponent;
    turnComponent->switchTurn(true);
    _entityManager->addComponentToEntity(player, new MoveComponent);
    _entityManager->addComponentToEntity(player, new PositionComponent{32, 0});
    _entityManager->addComponentToEntity(player, turnComponent);
    _entityManager->addComponentToEntity(player, new GravityComponent());

    DrawableComponent *drawableComponent2 = new DrawableComponent;
    drawableComponent2->shape = std::make_unique<ShapeSprite>(ShapeSprite(32, 48, 0, 0, "PlayerL_L1.png"));
    player = _entityManager->createEntity();
    _entityManager->addComponentToEntity(player, drawableComponent2);
    _entityManager->addComponentToEntity(player, new TurnComponent);
    _entityManager->addComponentToEntity(player, new MoveComponent);
    _entityManager->addComponentToEntity(player, new PositionComponent{576, 0});
    _entityManager->addComponentToEntity(player, new BoxCollider(32, 48));
    _entityManager->addComponentToEntity(player, new GravityComponent());

    TurnSystem* turnSystem = new TurnSystem {_entityManager};
    _systems.push_back(turnSystem);
    turnSystem->getRelevantEntities();
    turnSystem->setTurnTime(20);
}

void GameScreen::update(std::shared_ptr<KeyEvent> event) {
    if (event->getKey() == KEY::KEY_ESCAPE && event->getKeyEventType() == KeyEventType::Down) {
        _context->setActiveScreen<MainMenuScreen>();
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
    for (auto const &iterator : _systems) {
        iterator->update(deltaTime);
    }
}