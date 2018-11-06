#include <utility>

#include "../../Headers/StateMachine/GameScreen.h"
#include "../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../Headers/GameECS/Components/TurnComponent.h"
#include "../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../Headers/GameECS/Components/GravityComponent.h"
#include "../../Headers/GameECS/Components/DamageableComponent.h"
#include "../../Headers/GameECS/Systems/DamageableSystem.h"

GameScreen::GameScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context),
    _audioFacade(context->getFacade<AudioFacade>()),
    _entityManager(std::make_shared<EntityManager>()),
    _visualFacade(context->getFacade<VisualFacade>()){
    _inputFacade->getKeyEventObservable()->registerObserver(this);

    _systems.push_back(std::make_shared<DrawSystem>(_entityManager, _visualFacade));
    _systems.push_back(std::make_shared<MoveSystem>(_entityManager, _inputFacade));
    _systems.push_back(std::make_shared<GravitySystem>(_entityManager));

    //create two players
    teamOne[0] = _entityManager->createEntity();
    teamTwo[0] = _entityManager->createEntity();

    DrawableComponent* drawableComponent = new DrawableComponent;
    drawableComponent->shape = std::make_unique<ShapeSprite>(ShapeSprite({32, 48, 32, 0, "PlayerW_R0.png"}));
    _entityManager->addComponentToEntity(teamOne[0], drawableComponent);
    _entityManager->addComponentToEntity(teamOne[0], new BoxCollider(32, 48));
    TurnComponent* turnComponent = new TurnComponent;
    turnComponent->switchTurn(true);
    _entityManager->addComponentToEntity(teamOne[0], turnComponent);
    _entityManager->addComponentToEntity(teamOne[0], new GravityComponent());
    _entityManager->addComponentToEntity(teamOne[0], new DamageableComponent());

    DrawableComponent* drawableComponent2 = new DrawableComponent;
    drawableComponent2->shape = std::make_unique<ShapeSprite>(ShapeSprite(32, 48, 576, 0, "PlayerL_L1.png"));
    _entityManager->addComponentToEntity(teamTwo[0], drawableComponent2);
    _entityManager->addComponentToEntity(teamTwo[0], new TurnComponent);
    _entityManager->addComponentToEntity(teamTwo[0], new BoxCollider(32, 48));
    _entityManager->addComponentToEntity(teamTwo[0], new GravityComponent());
    _entityManager->addComponentToEntity(teamTwo[0], new DamageableComponent());

    std::shared_ptr<TurnSystem> turnSystem = std::make_shared<TurnSystem>(_entityManager);
    _systems.push_back(turnSystem);
    turnSystem->getRelevantEntities();
    turnSystem->setTurnTime(20);
    std::shared_ptr<DamageableSystem> damageSystem = std::make_shared<DamageableSystem>(_entityManager);
    _systems.push_back(damageSystem);
}

void GameScreen::update(std::shared_ptr<KeyEvent> event){
    if(event->getKey() == KEY::KEY_ESCAPE)
    {
        _context->setActiveScreen<MainMenuScreen>();
    }
    if (event->getKey() == KEY::KEY_A)
    {
        _entityManager->getComponentFromEntity<DamageableComponent>(teamTwo[0])->LowerHealth(10);
    }
}

GameScreen::~GameScreen() = default;

void GameScreen::update(double deltaTime) {
    std::map<int, std::shared_ptr<TurnComponent>> _entitiesWithTurnComponent = _entityManager->getAllEntitiesWithComponent<TurnComponent>();
    if(_entitiesWithTurnComponent.size() == 1)
    {
        MainMenuScreen screen(_context);
        //set score
        if (_entitiesWithTurnComponent.count(teamOne[0]) > 0) {
            //You won
        }
        else {
            //You lost
        }
        _context->setActiveScreen<MainMenuScreen>();
    } else if(_entitiesWithTurnComponent.empty()) {
        MainMenuScreen screen(_context);
        //set score
        //it's a draw!
        _context->setActiveScreen<MainMenuScreen>();
    }
    _audioFacade->playMusic("wildwest");
    _inputFacade->pollEvents();
    for(auto const &iterator : _systems) {
        iterator->update(deltaTime);
    }

}