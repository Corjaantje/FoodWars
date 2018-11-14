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
#include "../../Headers/GameECS/Systems/AnimationSystem.h"
#include "../../Headers/GameECS/Components/AnimationComponent.h"

GameScreen::GameScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context),
    _audioFacade(context->getFacade<AudioFacade>()),
    _entityManager(std::make_shared<EntityManager>()),
    _visualFacade(context->getFacade<VisualFacade>()){
    _inputFacade->getKeyEventObservable()->registerKeyEventObserver(this);
    _inputFacade->setWindowResolutionCalculator(_context->getWindowResolutionCalculator());
    std::shared_ptr<CollisionSystem> collisionSystem = std::make_shared<CollisionSystem>(_entityManager);

    _systems.push_back(std::make_shared<JumpSystem>(_entityManager, _inputFacade, _audioFacade, *collisionSystem.get()));
    _systems.push_back(std::make_shared<MoveSystem>(_entityManager, _inputFacade, *collisionSystem.get()));
    _systems.push_back(collisionSystem);
    _systems.push_back(std::make_shared<GravitySystem>(_entityManager, *collisionSystem.get()));
    _systems.push_back(std::make_shared<AnimationSystem>(_entityManager));
    _systems.push_back(std::make_shared<DrawSystem>(_entityManager, _visualFacade));
    int player = _entityManager->createEntity();

    std::vector<IShape*> idleAnimation;
    idleAnimation.push_back(new ShapeSprite{32, 48, 0, 0, "PlayerW_R0.png"});
    idleAnimation.push_back(new ShapeSprite{32, 48, 0, 0, "PlayerW_R1.png"});
    idleAnimation.push_back(new ShapeSprite{32, 48, 0, 0, "PlayerW_R2.png"});
    AnimationComponent* animationComponent = new AnimationComponent{idleAnimation, 0.1};
    _entityManager->addComponentToEntity(player, animationComponent);
    _entityManager->addComponentToEntity(player, new DrawableComponent);

    _entityManager->addComponentToEntity(player, new BoxCollider(32, 48));
    TurnComponent* turnComponent = new TurnComponent;
    turnComponent->switchTurn(true);
    _entityManager->addComponentToEntity(player, new MoveComponent);
    _entityManager->addComponentToEntity(player, new PositionComponent{32, 0});
    _entityManager->addComponentToEntity(player, turnComponent);
    _entityManager->addComponentToEntity(player, new GravityComponent());


    player = _entityManager->createEntity();
    AnimationComponent* animationComponent2 = new AnimationComponent{idleAnimation, 0.1};
    _entityManager->addComponentToEntity(player, animationComponent2);
    _entityManager->addComponentToEntity(player, new DrawableComponent);

    /*_entityManager->addComponentToEntity(player, drawableComponent2);*/
    _entityManager->addComponentToEntity(player, new TurnComponent);
    _entityManager->addComponentToEntity(player, new MoveComponent);
    _entityManager->addComponentToEntity(player, new PositionComponent{576, 0});
    _entityManager->addComponentToEntity(player, new BoxCollider(32, 48));
    _entityManager->addComponentToEntity(player, new GravityComponent());

    std::shared_ptr<TurnSystem> turnSystem = std::make_shared<TurnSystem>(_entityManager);
    _systems.push_back(turnSystem);
    turnSystem->getRelevantEntities();
    turnSystem->setTurnTime(20);
}

void GameScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE && event->getKeyEventType() == KeyEventType::Down)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}

GameScreen::~GameScreen() {
}

void GameScreen::update(double deltaTime) {
    _audioFacade->playMusic("nature");
    _inputFacade->pollEvents();
    for(auto const &iterator : _systems){
        iterator->update(deltaTime);
    }
}