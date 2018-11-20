#ifndef PROJECT_SWA_GAMESCREEN_H
#define PROJECT_SWA_GAMESCREEN_H

#include "IScreen.h"
#include "../GameECS/Systems/DrawSystem.h"
#include "../GameECS/Systems/MoveSystem.h"
#include "../GameECS/Systems/TurnSystem.h"
#include "../GameECS/Systems/GravitySystem.h"
#include "../GameECS/Systems/StorageSystem.h"
#include "Misc/Coordinate.h"
#include "Misc/GameLevel.h"

class GameScreen : public IScreen, public IObserver<KeyEvent> {
private:
    std::shared_ptr<EntityManager> _entityManager;
    std::string _wallpaper;
    std::string _backgroundMusic;
    std::vector<Coordinate> _spawnPoints;

    std::shared_ptr<AudioFacade> _audioFacade;
    std::shared_ptr<VisualFacade> _visualFacade;
    std::vector<IBaseSystem*> _systems;
    DrawSystem* drawSystem = nullptr;
    AnimationManager* _animationManager;
    StorageSystem* _storage;
public:
    explicit GameScreen(const std::shared_ptr<ScreenStateManager>& context, GameLevel* gameLevel);
    ~GameScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;
    void spawnPlayers();
    void addBackground();
};

#endif //PROJECT_SWA_GAMESCREEN_H