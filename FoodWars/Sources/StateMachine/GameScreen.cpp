#include "../../Headers/GameECS/Components/MoveComponent.h"
#include "../../Headers/GameECS/Systems/CollisionSystem.h"
#include "../../Headers/GameECS/Systems/JumpSystem.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../Headers/StateMachine/PauseScreen.h"
#include "../../Headers/GameECS/Systems/AnimationSystem.h"
#include "../../Headers/GameECS/Components/AnimationComponent.h"
#include "../../Headers/GameECS/Systems/DamageableSystem.h"
#include "../../Headers/StateMachine/DrawTransitionScreen.h"
#include "../../Headers/StateMachine/WinTransitionScreen.h"
#include "../../Headers/StateMachine/LoseTransitionScreen.h"

GameScreen::GameScreen(ScreenStateManager& context, GameLevel* gameLevel) : IScreen(context),
    _entityManager(std::make_shared<EntityManager>(gameLevel->getEntityManager())),
    _spawnPoints(gameLevel->getSpawnPoints()) {
    _inputFacade->getKeyEventObservable().registerKeyEventObserver(this);
    int background = _entityManager->createEntity();
    auto *comp = new DrawableComponent();
    comp->shape = createShape<ShapeSprite>(1600,900,0,0, gameLevel->getBackgroundWallpaper());
    comp->shape->layer = 0;
    _entityManager->addComponentToEntity(background, comp);

    _backgroundMusic = gameLevel->getBackgroundMusic();
    _animationManager = new AnimationManager{};
    CollisionSystem* collisionSystem = new CollisionSystem{ _entityManager };
    _systems.push_back(new JumpSystem { _entityManager, *_audioFacade, *_inputFacade, *collisionSystem } );
    _systems.push_back(new MoveSystem { _entityManager, *_inputFacade, *collisionSystem });
    _systems.push_back(new GravitySystem { _entityManager, *collisionSystem });
    _systems.push_back(new AnimationSystem {_entityManager, _animationManager });
    _systems.push_back(new TurnSystem {_entityManager});
    _shootingSystem = new ShootingSystem(_entityManager, *_audioFacade, *_visualFacade, *_inputFacade);
    _systems.push_back(_shootingSystem);
    _systems.push_back(new DamageableSystem { _entityManager, *collisionSystem});
    _systems.push_back(collisionSystem);
    drawSystem = new DrawSystem {_entityManager, *_visualFacade};
    _systems.push_back(drawSystem);

    int count = 0;
    for (auto const& t : _entityManager->getAllEntitiesWithComponent<TurnComponent>())
    {
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

        if (event.getKey() == KEY::KEY_G){
            _shootingSystem->toggleShooting();
        }
        //Toggle Framerate
        if(event.getKey() == KEY::KEY_F){
            drawSystem->toggleFpsCounter();
        }
    }
}

GameScreen::~GameScreen() {
    for (auto const &iterator : _systems) {
        delete iterator;
    }
    delete _animationManager;
};

void GameScreen::update(double deltaTime) {
    std::map<int, std::shared_ptr<TurnComponent>> _entitiesWithTurnComponent = _entityManager->getAllEntitiesWithComponent<TurnComponent>();
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
    _audioFacade->playMusic(_backgroundMusic.c_str());
    _inputFacade->pollEvents();
    for(auto const &iterator : _systems){
        iterator->update(deltaTime * _context->getTimeModifier());
    }
}




