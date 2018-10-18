#include "../../Headers/StateMachine/GameScreen.h"
#include "../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../Headers/GameECS/Components/TurnComponent.h"
#include "../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../Headers/GameECS/Components/GravityComponent.h"

GameScreen::GameScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context),
        _entityManager(std::make_shared<EntityManager>()),
        _visualFacade(context->getFacade<VisualFacade>()),
        _drawSystem(_entityManager, _visualFacade),
        _moveSystem(_entityManager, _inputFacade),
        _turnSystem(_entityManager),
        _gravitySystem(_entityManager),
        _inputFacade(std::make_shared<InputFacade>()) {
    int player = _entityManager->createEntity();

    DrawableComponent* drawableComponent = new DrawableComponent;
    drawableComponent->shape = std::make_unique<ShapeRectangle>(ShapeRectangle({32, 32, 0, 0, Colour{0, 255, 0, 100}}));
    _entityManager->addComponentToEntity(player, drawableComponent);
    _entityManager->addComponentToEntity(player, new BoxCollider(32, 32));
    TurnComponent* turnComponent = new TurnComponent;
    turnComponent->switchTurn(true);
    _entityManager->addComponentToEntity(player, turnComponent);
    _entityManager->addComponentToEntity(player, new GravityComponent());


    DrawableComponent* drawableComponent2 = new DrawableComponent;
    drawableComponent2->shape = std::make_unique<ShapeRectangle>(ShapeRectangle(32, 32, 500, 0, Colour{255, 0, 0, 100}));
    player = _entityManager->createEntity();
    _entityManager->addComponentToEntity(player, drawableComponent2);
    _entityManager->addComponentToEntity(player, new TurnComponent);
    _entityManager->addComponentToEntity(player, new BoxCollider(32, 32));
    _entityManager->addComponentToEntity(player, new GravityComponent());

    _turnSystem.getRelevantEntities();
    _turnSystem.setTurnTime(30);

    //Initialize the Entity Manager
    //Initialize the DrawSystem.
}

GameScreen::~GameScreen() {
}

void GameScreen::update(double deltaTime) {
    _inputFacade->pollEvents();
    _turnSystem.update(deltaTime);
    _moveSystem.update(deltaTime);
    _drawSystem.update(deltaTime);
    _gravitySystem.update(deltaTime);
}