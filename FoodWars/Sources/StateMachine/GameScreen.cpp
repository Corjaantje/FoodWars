#include <utility>

#include <utility>
#include "../../Headers/StateMachine/GameScreen.h"
#include "../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../../Headers/GameECS/Components/TurnComponent.h"
#include "../../Headers/GameECS/Components/Collider/BoxCollider.h"
#include "../../Headers/GameECS/Components/GravityComponent.h"
#include "../../Headers/GameECS/Components/MoveComponent.h"
#include "../../Headers/GameECS/Systems/CollisionSystem.h"
#include "../../Headers/GameECS/Systems/JumpSystem.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../Headers/StateMachine/PauseScreen.h"
#include "../../Headers/GameECS/Systems/AnimationSystem.h"
#include "../../Headers/GameECS/Components/AnimationComponent.h"

GameScreen::GameScreen(const std::shared_ptr<ScreenStateManager>& context, GameLevel* gameLevel) :
    IScreen(context),
    _entityManager(std::make_shared<EntityManager>(gameLevel->getEntityManager())),
    _spawnPoints(gameLevel->getSpawnPoints())
{
    std::string level = gameLevel->getBackgroundWallpaper();
    _wallpaper = level;

    std::string music = gameLevel->getBackgroundMusic();
    _backgroundMusic = music;


    _audioFacade = _context->getFacade<AudioFacade>();
    _visualFacade = _context->getFacade<VisualFacade>();
    _inputFacade->getKeyEventObservable()->registerKeyEventObserver(this);

    // Build level
    addBackground();
    spawnPlayers();


    _animationManager = new AnimationManager{};
    CollisionSystem* collisionSystem = new CollisionSystem{ _entityManager };
    _systems.push_back(new JumpSystem { _entityManager, _inputFacade, _audioFacade, *collisionSystem} );
    _systems.push_back(new MoveSystem{ _entityManager, _inputFacade, *collisionSystem});
    _systems.push_back(collisionSystem);
    _systems.push_back(new GravitySystem { _entityManager, *collisionSystem });
    _systems.push_back(new AnimationSystem(_entityManager, _animationManager));
    _systems.push_back(new DrawSystem {_entityManager, _visualFacade});
    _systems.push_back(new TurnSystem {_entityManager});
}

void GameScreen::spawnPlayers() {
    /*std::vector<IShape*> spawnAnimation2;
    spawnAnimation2.push_back(new ShapeSprite{48, 72, 1500, 300, "PlayerW_L0.png"});
    AnimationComponent* animationComponent2 = new AnimationComponent{spawnAnimation2, 0.1};*/

    for(const auto &iterator : _spawnPoints) {
        // Spawn Location and animation interval
        std::vector<IShape*> spawnAnimation;
        //TODO: replace png depending on teamcomponent
        spawnAnimation.push_back(new ShapeSprite{48, 72, iterator.getXCoord(), iterator.getYCoord(), "PlayerW_R0.png"});
        AnimationComponent* animationComponent = new AnimationComponent{spawnAnimation, 0.1};

        // TurnComponent
        auto turnComponent = new TurnComponent;
        turnComponent->switchTurn(true);
        turnComponent->setRemainingTime(30);

        // Player
        int player = _entityManager->createEntity();
        _entityManager->addComponentToEntity(player, new DrawableComponent);
        _entityManager->addComponentToEntity(player, new BoxCollider(48, 72));
        _entityManager->addComponentToEntity(player, new PositionComponent(32,0));
        _entityManager->addComponentToEntity(player, turnComponent);
        _entityManager->addComponentToEntity(player, new MoveComponent);
        _entityManager->addComponentToEntity(player, new GravityComponent());
        _entityManager->addComponentToEntity(player, animationComponent);
    }


   /* // Player 2
    player = _entityManager->createEntity();
    _entityManager->addComponentToEntity(player, new DrawableComponent);
    _entityManager->addComponentToEntity(player, new BoxCollider(48, 72));
    _entityManager->addComponentToEntity(player, new PositionComponent(576,0));
    _entityManager->addComponentToEntity(player, new TurnComponent);
    _entityManager->addComponentToEntity(player, new MoveComponent);
    _entityManager->addComponentToEntity(player, new GravityComponent());
    _entityManager->addComponentToEntity(player, animationComponent2);*/
}

void GameScreen::addBackground() {
    int background = _entityManager->createEntity();
    auto *comp = new DrawableComponent();
    //TODO: use sprite
    comp->shape = new ShapeSprite{1600,900,0,0, _wallpaper};
    _entityManager->addComponentToEntity(background, comp);
}


void GameScreen::update(std::shared_ptr<KeyEvent> event){
    if (event->getKeyEventType() == KeyEventType::Down) {
        if(event->getKey() == KEY::KEY_ESCAPE)
            _context->setActiveScreen<PauseScreen>();

        //Adjusting gamespeed
        if(event->getKey() == KEY::KEY_PAGEUP) {
            _context->setTimeModifier(2.50);
        }
        if(event->getKey() == KEY::KEY_PAGEDOWN) {
            _context->setTimeModifier(0.40);
        }
        if(event->getKey() == KEY::KEY_HOME) {
            _context->setTimeModifier(1);
        }

        //Toggle Framerate
        if(event->getKey() == KEY::KEY_F){
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
    _audioFacade->playMusic(_backgroundMusic.c_str());
    _inputFacade->pollEvents();
    for(auto const &iterator : _systems){
        iterator->update(deltaTime * _context->getTimeModifier());
    }
}




