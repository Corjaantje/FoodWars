#include <utility>
#include "../../Headers/StateMachine/GameScreen.h"
#include "../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../Headers/GameECS/Components/TurnComponent.h"
#include "../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../Headers/GameECS/Components/GravityComponent.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"

GameScreen::GameScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context),
    _audioFacade(context->getFacade<AudioFacade>()),
    _entityManager(std::make_shared<EntityManager>()),
    _visualFacade(context->getFacade<VisualFacade>()){
    _inputFacade->getKeyEventObservable()->registerObserver(this);
    _systems.push_back(std::make_shared<DrawSystem>(_entityManager, _visualFacade));
    _systems.push_back(std::make_shared<MoveSystem>(_entityManager, _inputFacade));
    _systems.push_back(std::make_shared<GravitySystem>(_entityManager));
    int player = _entityManager->createEntity();

    DrawableComponent* drawableComponent = new DrawableComponent;
    drawableComponent->shape = std::make_unique<ShapeSprite>(ShapeSprite({32, 48, 32, 0, "PlayerW_R0.png"}));
    _entityManager->addComponentToEntity(player, drawableComponent);
    _entityManager->addComponentToEntity(player, new BoxCollider(32, 48));
    TurnComponent* turnComponent = new TurnComponent;
    turnComponent->switchTurn(true);
    _entityManager->addComponentToEntity(player, turnComponent);
    _entityManager->addComponentToEntity(player, new GravityComponent());


    DrawableComponent* drawableComponent2 = new DrawableComponent;
    drawableComponent2->shape = std::make_unique<ShapeSprite>(ShapeSprite(32, 48, 576, 0, "PlayerL_L1.png"));
    player = _entityManager->createEntity();
    _entityManager->addComponentToEntity(player, drawableComponent2);
    _entityManager->addComponentToEntity(player, new TurnComponent);
    _entityManager->addComponentToEntity(player, new BoxCollider(32, 48));
    _entityManager->addComponentToEntity(player, new GravityComponent());

    std::shared_ptr<TurnSystem> turnSystem = std::make_shared<TurnSystem>(_entityManager);
    _systems.push_back(turnSystem);
    turnSystem->getRelevantEntities();
    turnSystem->setTurnTime(20);
}

void GameScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
}

GameScreen::~GameScreen() {
}

void GameScreen::update(double deltaTime) {
    _audioFacade->playMusic("wildwest");
    _inputFacade->pollEvents();
    for(auto const &iterator : _systems){
        iterator->update(deltaTime);
    }
}