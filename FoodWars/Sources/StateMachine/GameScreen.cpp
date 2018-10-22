#include "../../Headers/StateMachine/GameScreen.h"
#include "../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../Headers/GameECS/Components/TurnComponent.h"
#include "../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../Headers/GameECS/Components/GravityComponent.h"

GameScreen::GameScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context),
        _entityManager(std::make_shared<EntityManager>()),
        _visualFacade(context->getFacade<VisualFacade>()),
        _inputFacade(std::make_shared<InputFacade>()) {
    _systems.push_back(std::make_shared<DrawSystem>(_entityManager, _visualFacade));
    _systems.push_back(std::make_shared<MoveSystem>(_entityManager, _inputFacade));
    _systems.push_back(std::make_shared<GravitySystem>(_entityManager));
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

    std::shared_ptr<TurnSystem> turnSystem = std::make_shared<TurnSystem>(_entityManager);
    _systems.push_back(turnSystem);
    turnSystem->getRelevantEntities();
    turnSystem->setTurnTime(20);
}

GameScreen::~GameScreen() {
}

void GameScreen::update(double deltaTime) {
    _inputFacade->pollEvents();
    for(auto const &iterator : _systems){
        iterator->update(deltaTime);
    }
}