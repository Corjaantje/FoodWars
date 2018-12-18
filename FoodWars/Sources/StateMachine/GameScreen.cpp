#include "../../Headers/StateMachine/GameScreen.h"
#include "../../Headers/GameECS/Components/MoveComponent.h"
#include "../../Headers/GameECS/Systems/CollisionSystem.h"
#include "../../Headers/GameECS/Systems/JumpSystem.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/StateMachine/PauseScreen.h"
#include "../../Headers/GameECS/Systems/AnimationSystem.h"
#include "../../Headers/GameECS/Systems/DamageableSystem.h"
#include "../../Headers/StateMachine/LevelTransitionScreen.h"
#include "../../Headers/GameECS/Systems/AISystem.h"
#include "../../Headers/GameECS/Systems/PowerupSystem.h"


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
    _turnSystem = new TurnSystem(*_entityManager);
    _systems.push_back(std::unique_ptr<TurnSystem>(_turnSystem));
    auto shootingSystem = new ShootingSystem{*_entityManager, *_audioFacade, *_visualFacade, *_inputFacade};
    _systems.push_back(std::unique_ptr<ShootingSystem>(shootingSystem));
    _systems.push_back(std::make_unique<AISystem>(*_entityManager, *_audioFacade, *collisionSystem));
    _systems.push_back(std::make_unique<DamageableSystem>(*_entityManager, *_audioFacade, *collisionSystem));
    _systems.push_back(std::unique_ptr<CollisionSystem>(collisionSystem));
    _systems.push_back(std::make_unique<PowerupSystem>(*collisionSystem, *_turnSystem, *_entityManager));
    auto drawSystem = new DrawSystem{*_entityManager, *_visualFacade, *_inputFacade, *shootingSystem};
    _systems.push_back(std::unique_ptr<DrawSystem>(drawSystem));
    nextButton = createShape<FlashingTextButton>(_inputFacade->getMouseEventObservable(),"Next", [this]()
                                         {
                                             _turnSystem->switchTurn();
                                             nextButton->setFlashing(false);
                                             nextButton->setTextColor(Colour(255,255,255,0));
                                         },
                                         110, 40, 800-30, 135, Colour(255,255,255,0), Colour(255,255,255,0));
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

    _keyMap[KEY::KEY_ESCAPE] = [c = _context]() {
        c->createOrSetActiveScreen<PauseScreen>();
    };
    _keyMap[KEY::KEY_PAGEUP] = [c = _context]() {
        c->setTimeModifier(c->getTimeModifier() + 0.2);
    };
    _keyMap[KEY::KEY_PAGEDOWN] = [c = _context]() {
        c->setTimeModifier(c->getTimeModifier() - 0.2);
    };
    _keyMap[KEY::KEY_HOME] = [c = _context]() {
        c->setTimeModifier(1.00);
    };
    _keyMap[KEY::KEY_S] = [s = shootingSystem]() {
        s->toggleShooting();
    };
    _keyMap[KEY::KEY_F] = [d = drawSystem]() {
        d->toggleFpsCounter();
    };
    _keyMap[KEY::KEY_T] = [t = _turnSystem]() {
        t->resetCurrentTime();
    };
    _keyMap[KEY::KEY_R] = [e = _entityManager, t = _turnSystem]() {
        e->getComponentFromEntity<PlayerComponent>(t->getCurrentPlayerID())->getSelectedWeapon()->setAmmo(100);
    };
    _keyMap[KEY::KEY_Y] = [t = _turnSystem]() {
        t->resetCurrentEnergy();
    };
    _keyMap[KEY::KEY_U] = [e = _entityManager, t = _turnSystem]() {
        e->getComponentFromEntity<DamageableComponent>(t->getCurrentPlayerID())->setResistance(100);
    };
    _keyMap[KEY::KEY_K] = [t = _turnSystem, p1 = playerOne, p2 = playerTwo, e = _entityManager]() {
        if (t->getCurrentPlayerID() == p1) {
            e->getComponentFromEntity<DamageableComponent>(p2)->destroy();
        } else {
            e->getComponentFromEntity<DamageableComponent>(p1)->destroy();
        }
    };
}

void GameScreen::update(const KeyEvent& event){
    if (event.getKeyEventType() == KeyEventType::Down) {
        if(_keyMap.count(event.getKey()) > 0) {
            _keyMap.at(event.getKey())();
        }
    }
}

GameScreen::~GameScreen() = default;

void GameScreen::update(double deltaTime) {
    if (_turnSystem->getCurrentPlayerEnergy() <= 1) nextButton->setFlashing(true);
    bool playerOneAlive = true;
    bool playerTwoAlive = true;
    int playerOneScore = 0;
    int playerTwoScore = 0;
    for (auto const &iterator : _entityManager->getAllEntitiesWithComponent<PlayerComponent>()) {
        if(iterator.second->getPlayerID() == 1){
            playerOneAlive = iterator.second->isAlive();
            playerOneScore = iterator.second->getScore();
        }
        if(iterator.second->getPlayerID() == 2){
            playerTwoAlive = iterator.second->isAlive();
            playerTwoScore = iterator.second->getScore();
        }
    }
    //Either of the 2 died
    if(!playerOneAlive || !playerTwoAlive){
        _context->setActiveScreen(std::make_unique<LevelTransitionScreen>(*_context, !playerOneAlive, !playerTwoAlive, playerOneScore, playerTwoScore));
    }
    _audioFacade->playMusic(_gameLevel->getBackgroundMusic().c_str());
    _inputFacade->pollEvents();
    for(auto const &iterator : _systems){
        iterator->update(deltaTime * _context->getTimeModifier());
    }
}