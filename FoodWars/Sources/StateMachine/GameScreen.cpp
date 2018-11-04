#include <utility>

#include "../../Headers/StateMachine/GameScreen.h"
#include "../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../Headers/GameECS/Components/TurnComponent.h"
#include "../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../Headers/GameECS/Components/GravityComponent.h"
#include "../../Headers/GameECS/Components/DamageableComponent.h"

GameScreen::GameScreen(std::shared_ptr<ScreenStateManager> context) : IScreen(context),
    _audioFacade(context->getFacade<AudioFacade>()),
    _entityManager(std::make_shared<EntityManager>()),
    _visualFacade(context->getFacade<VisualFacade>()){
    _inputFacade->getKeyEventObservable()->registerObserver(this);

    _systems.push_back(std::make_shared<DrawSystem>(_entityManager, _visualFacade));
    _systems.push_back(std::make_shared<MoveSystem>(_entityManager, _inputFacade));
    _systems.push_back(std::make_shared<GravitySystem>(_entityManager));

    int playerOne = _entityManager->createEntity();
    DrawableComponent* drawableComponent = new DrawableComponent;
    drawableComponent->shape = std::make_unique<ShapeSprite>(ShapeSprite({32, 48, 32, 0, "PlayerW_R0.png"}));
    _entityManager->addComponentToEntity(playerOne, drawableComponent);
    _entityManager->addComponentToEntity(playerOne, new BoxCollider(32, 48));
    TurnComponent* turnComponent = new TurnComponent;
    turnComponent->switchTurn(true);
    _entityManager->addComponentToEntity(playerOne, turnComponent);
    _entityManager->addComponentToEntity(playerOne, new GravityComponent());
    _entityManager->addComponentToEntity(playerOne, new DamageableComponent());

    DrawableComponent* drawableComponent2 = new DrawableComponent;
    drawableComponent2->shape = std::make_unique<ShapeSprite>(ShapeSprite(32, 48, 576, 0, "PlayerL_L1.png"));
    int playerTwo = _entityManager->createEntity();
    _entityManager->addComponentToEntity(playerTwo, drawableComponent2);
    _entityManager->addComponentToEntity(playerTwo, new TurnComponent);
    _entityManager->addComponentToEntity(playerTwo, new BoxCollider(32, 48));
    _entityManager->addComponentToEntity(playerTwo, new GravityComponent());
    _entityManager->addComponentToEntity(playerTwo, new DamageableComponent());

    DrawableComponent* playerHPbutton = new DrawableComponent();
    playerHPbutton->shape = std::make_unique<Button>(Button(*_inputFacade->getMouseEventObservable(), "Health - 10",
                                                                []() { SDL_Log("Test"); },
                                                                250, 60, 200, 200));

    DrawableComponent* playerHPtext = new DrawableComponent;
    playerHPtext->shape = std::make_unique<ShapeText>(ShapeText(200, 60, std::to_string(_entityManager->getComponentFromEntity<DamageableComponent>(playerTwo)->GetHealth()), 12, 20, 20, Colour(0,0,0,0)));

    int playerHP = _entityManager->createEntity();
    _entityManager->addComponentToEntity(playerHP, playerHPtext);
    int playerHP2 = _entityManager->createEntity();
    //_entityManager->addComponentToEntity(playerHP2, playerHPbutton);

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
    if (event->getKey() == KEY::KEY_A)
    {
        std::vector<int> _turnOrder;
        std::map<int, std::shared_ptr<TurnComponent>> test = _entityManager->getAllEntitiesWithComponent<TurnComponent>();
        for (auto const& x : test)
        {
            _turnOrder.push_back(x.first);
        }
        _entityManager->getComponentFromEntity<DamageableComponent>(_turnOrder[1])->LowerHealth(10);
        if (!_entityManager->getComponentFromEntity<DamageableComponent>(_turnOrder[1])->IsAlive())
        {
            std::cout << "You won!" << std::endl;
            _context->setActiveScreen<MainMenuScreen>();
        } else {
            std::cout << _entityManager->getComponentFromEntity<DamageableComponent>(_turnOrder[1])->GetHealth() << std::endl;
        }
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