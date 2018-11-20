#include <utility>
#include "../../Headers/StateMachine/GameScreen.h"
#include "../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../../Headers/GameECS/Systems/CollisionSystem.h"
#include "../../Headers/GameECS/Systems/JumpSystem.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"
#include "../../Headers/GameECS/Components/DrawableComponent.h"
#include "../../Headers/StateMachine/PauseScreen.h"
#include "../../Headers/GameECS/Systems/AnimationSystem.h"
#include "../../Headers/GameECS/Components/AnimationComponent.h"
#include "../../Headers/GameECS/Systems/DamageableSystem.h"

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
    _systems.push_back(new JumpSystem { _entityManager, _inputFacade, audioFacade, *collisionSystem } );
    _systems.push_back(new MoveSystem { _entityManager, _inputFacade, *collisionSystem });
    _systems.push_back(new GravitySystem { _entityManager, *collisionSystem });
    _systems.push_back(new AnimationSystem(_entityManager, _animationManager));
    _systems.push_back(new DrawSystem {_entityManager, _visualFacade, _inputFacade});
    TurnSystem* turnSystem = new TurnSystem {_entityManager};
    _systems.push_back(turnSystem);
    _shootingSystem = new ShootingSystem(_entityManager, audioFacade, visualFacade, _inputFacade);
    _systems.push_back(_shootingSystem);
    _systems.push_back(new DamageableSystem { _entityManager, *collisionSystem});
    _systems.push_back(collisionSystem);

    drawSystem = new DrawSystem {_entityManager, visualFacade, _inputFacade};
    _systems.push_back(drawSystem);
}

void GameScreen::spawnPlayers() {
    /*std::vector<IShape*> spawnAnimation2;
    spawnAnimation2.push_back(new ShapeSprite{48, 72, 1500, 300, "PlayerW_L0.png"});
    AnimationComponent* animationComponent2 = new AnimationComponent{spawnAnimation2, 0.1};*/
    if(!_spawnPoints.empty())
    {
        // TurnComponent
        auto turnComponent = new TurnComponent;
        turnComponent->switchTurn(true);
        turnComponent->setRemainingTime(5);

        // Spawn Location and animation interval
        std::vector<IShape*> spawnAnimation;
        //TODO: replace png depending on teamcomponent
        spawnAnimation.push_back(new ShapeSprite{48, 72, _spawnPoints[0].getXCoord(), _spawnPoints[0].getYCoord(), "PlayerW_R0.png"});
        AnimationComponent* animationComponent = new AnimationComponent{spawnAnimation, 0.1};

        // Player
        int player = _entityManager->createEntity();
        _entityManager->addComponentToEntity(player, new DrawableComponent);
        _entityManager->addComponentToEntity(player, new BoxCollider(48, 72));
        _entityManager->addComponentToEntity(player, new PositionComponent(_spawnPoints[0].getXCoord(),_spawnPoints[0].getYCoord()));
        _entityManager->addComponentToEntity(player, turnComponent);
        _entityManager->addComponentToEntity(player, new MoveComponent);
        _entityManager->addComponentToEntity(player, new GravityComponent());
        _entityManager->addComponentToEntity(player, animationComponent);
        _entityManager->addComponentToEntity(player, new DamageableComponent);

        std::vector<IShape*> spawnAnimation2;
        spawnAnimation2.push_back(new ShapeSprite{48, 72, _spawnPoints[1].getXCoord(), _spawnPoints[1].getYCoord(), "PlayerG_R0.png"});
        AnimationComponent* animationComponent2 = new AnimationComponent{spawnAnimation2, 0.1};

        // Player
        player = _entityManager->createEntity();
        _entityManager->addComponentToEntity(player, new DrawableComponent);
        _entityManager->addComponentToEntity(player, new BoxCollider(48, 72));
        _entityManager->addComponentToEntity(player, new PositionComponent(_spawnPoints[1].getXCoord(), _spawnPoints[1].getYCoord()));
        _entityManager->addComponentToEntity(player, new TurnComponent);
        _entityManager->addComponentToEntity(player, new MoveComponent);
        _entityManager->addComponentToEntity(player, new GravityComponent());
        _entityManager->addComponentToEntity(player, animationComponent2);
        _entityManager->addComponentToEntity(player, new DamageableComponent);
    }


    /*for(const auto &iterator : _spawnPoints) {

        // TurnComponent
        auto turnComponent = new TurnComponent;
        turnComponent->switchTurn(true);
        turnComponent->setRemainingTime(5);

        // Spawn Location and animation interval
        std::vector<IShape*> spawnAnimation;
        //TODO: replace png depending on teamcomponent
        spawnAnimation.push_back(new ShapeSprite{48, 72, iterator.getXCoord(), iterator.getYCoord(), "PlayerW_R0.png"});
        AnimationComponent* animationComponent = new AnimationComponent{spawnAnimation, 0.1};

        // Player
        int player = _entityManager->createEntity();
        _entityManager->addComponentToEntity(player, new DrawableComponent);
        _entityManager->addComponentToEntity(player, new BoxCollider(48, 72));
        _entityManager->addComponentToEntity(player, new PositionComponent(32,0));
        _entityManager->addComponentToEntity(player, turnComponent);
        _entityManager->addComponentToEntity(player, new MoveComponent);
        _entityManager->addComponentToEntity(player, new GravityComponent());
        _entityManager->addComponentToEntity(player, animationComponent);
    }*/


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
    //int background = _entityManager->createEntity();
    //auto *comp = new DrawableComponent();
    _renderList._shapes[1].push_back(createShape<ShapeSprite>(1600,900,0,0, _wallpaper));
    //_entityManager->addComponentToEntity(background, comp);
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

        if (event->getKey() == KEY::KEY_G){
            _shootingSystem->toggleShooting();
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
    std::map<int, std::shared_ptr<TurnComponent>> _entitiesWithTurnComponent = _entityManager->getAllEntitiesWithComponent<TurnComponent>();
    if(_entitiesWithTurnComponent.size() == 1)
    {
        //set score
        //check win/lose
        _context->setActiveScreen<MainMenuScreen>();
    } else if(_entitiesWithTurnComponent.empty()) {
        //set score
        //it's a draw!
        _context->setActiveScreen<MainMenuScreen>();
    }
    _audioFacade->playMusic(_backgroundMusic.c_str());
    _inputFacade->pollEvents();
    for(auto const &iterator : _systems){
        iterator->update(deltaTime * _context->getTimeModifier());
    }
}




