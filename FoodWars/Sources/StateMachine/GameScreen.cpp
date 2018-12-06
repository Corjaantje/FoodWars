#include "../../Headers/GameECS/Components/MoveComponent.h"
#include "../../Headers/GameECS/Systems/CollisionSystem.h"
#include "../../Headers/GameECS/Systems/JumpSystem.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/StateMachine/PauseScreen.h"
#include "../../Headers/GameECS/Systems/AnimationSystem.h"
#include "../../Headers/GameECS/Systems/DamageableSystem.h"
#include "../../Headers/StateMachine/DrawTransitionScreen.h"
#include "../../Headers/StateMachine/WinTransitionScreen.h"
#include "../../Headers/StateMachine/LoseTransitionScreen.h"
#include "../../../TonicEngine/Headers/Visual/FlashingColour.h"

GameScreen::GameScreen(ScreenStateManager& context, std::unique_ptr<GameLevel> &gameLevel) :
        IScreen(context), _gameLevel(std::move(gameLevel)), _entityManager(&_gameLevel->getEntityManager()) {
    int background = _entityManager->createEntity();
    _entityManager->addComponentToEntity<DrawableComponent>(background, std::make_unique<ShapeSprite>(1600,900,0,0, _gameLevel->getBackgroundWallpaper(), 0));
    _inputFacade->getKeyEventObservable().registerKeyEventObserver(this);

    auto collisionSystem = new CollisionSystem{*_entityManager};
    _systems.push_back(std::make_unique<JumpSystem>(*_entityManager, *_audioFacade, *_inputFacade, *collisionSystem));
    _systems.push_back(std::make_unique<MoveSystem>(*_entityManager, *_inputFacade, *collisionSystem));
    _systems.push_back(std::make_unique<GravitySystem>(*_entityManager, *collisionSystem));
    _systems.push_back(std::make_unique<AnimationSystem>(*_entityManager));
    auto turnSystem = new TurnSystem(*_entityManager);
    _systems.push_back(std::unique_ptr<TurnSystem>(turnSystem));
    _shootingSystem = new ShootingSystem{*_entityManager, *_audioFacade, *_visualFacade, *_inputFacade};
    _systems.push_back(std::unique_ptr<ShootingSystem>(_shootingSystem));
    _systems.push_back(std::make_unique<DamageableSystem>(*_entityManager, *_audioFacade, *collisionSystem));
    _systems.push_back(std::unique_ptr<CollisionSystem>(collisionSystem));
    drawSystem = new DrawSystem{*_entityManager, *_visualFacade, *_inputFacade};
    _systems.push_back(std::unique_ptr<DrawSystem>(drawSystem));
    nextButton = createShape<FlashingTextButton>(_inputFacade->getMouseEventObservable(),"Next", [turnSystem, this]()
                                         {
                                             turnSystem->switchTurn();
                                             nextButton->setFlashing(false);
                                             nextButton->setTextColor(Colour(255,255,255,0));
                                         },
                                         110, 40, 800-30, 135, Colour(0,0,0,0), Colour(0,0,0,0));
    nextButton->setFlashColours({{Colour(255,255,255,0)}, Colour(255,0,0,0)});
    nextButton->setInterval(0.5);
    nextButton->setFlashing(false);
    drawSystem->addShape(nextButton);
    int count = 0;
    for (auto const &t : _entityManager->getAllEntitiesWithComponent<TurnComponent>()) {
        if (count == 0) playerOne = t.first;
        else playerTwo = t.first;
        count++;
    }
}

void GameScreen::update(const KeyEvent& event){
    if (event.getKeyEventType() == KeyEventType::Down) {
        if(event.getKey() == KEY::KEY_ESCAPE){
            _context->createOrSetActiveScreen<PauseScreen>();
        }

        //Adjusting gamespeed
        if(event.getKey() == KEY::KEY_PAGEUP) {
            _context->setTimeModifier(2.50);
        }
        if(event.getKey() == KEY::KEY_PAGEDOWN) {
            _context->setTimeModifier(0.40);
        }
        if(event.getKey() == KEY::KEY_HOME) {
            _context->setTimeModifier(1);
        }

        if (event.getKey() == KEY::KEY_S){
            _shootingSystem->toggleShooting();
        }
        //Toggle Framerate
        if(event.getKey() == KEY::KEY_F){
            drawSystem->toggleFpsCounter();
        }
    }
}

GameScreen::~GameScreen() = default;

void GameScreen::update(double deltaTime) {
    std::map<int, TurnComponent *> _entitiesWithTurnComponent = _entityManager->getAllEntitiesWithComponent<TurnComponent>();
    if (!nextButton->getFlashing()){
        for ( auto const& turn : _entitiesWithTurnComponent)
        {
            if (turn.second->isMyTurn() && turn.second->getEnergy() <= 1)
            {
                nextButton->setFlashing(true);
                break;
            }
        }
    }

    if(_entitiesWithTurnComponent.size() == 1)
    {
        if (_entityManager->exists(playerOne)) {
            _context->setActiveScreen(std::make_unique<WinTransitionScreen>(*_context));
        }
        else {
            _context->setActiveScreen(std::make_unique<LoseTransitionScreen>(*_context));
        }
        //((std::static_pointer_cast<LevelTransitionScreen>(_context->getCurrentState())->setScore(100)));
    } else if(_entitiesWithTurnComponent.empty()) {
        _context->setActiveScreen(std::make_unique<DrawTransitionScreen>(*_context));
        //((std::static_pointer_cast<LevelTransitionScreen>(_context->getCurrentState())->setScore(100)));
    }
    _audioFacade->playMusic(_gameLevel->getBackgroundMusic().c_str());
    _inputFacade->pollEvents();
    for(auto const &iterator : _systems){
        iterator->update(deltaTime * _context->getTimeModifier());
    }
}