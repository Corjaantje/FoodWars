#ifndef PROJECT_SWA_GAMESCREEN_H
#define PROJECT_SWA_GAMESCREEN_H

#include "IScreen.h"
#include "../GameECS/Systems/DrawSystem.h"
#include "../GameECS/Systems/MoveSystem.h"
#include "../GameECS/Systems/TurnSystem.h"
#include "../GameECS/Systems/GravitySystem.h"
#include "../GameECS/Systems/ShootingSystem.h"
#include "../GameECS/Systems/StorageSystem.h"
#include "Misc/Coordinate.h"
#include "Misc/GameLevel.h"

class GameScreen : public IScreen, public IObserver<KeyEvent> {
private:
    std::shared_ptr<EntityManager> _entityManager;
    std::string _backgroundMusic;
    std::vector<Coordinate> _spawnPoints;
    std::vector<IBaseSystem*> _systems;
    DrawSystem* drawSystem;
    AnimationManager* _animationManager;
    ShootingSystem* _shootingSystem;
    int playerOne;
    int playerTwo;
public:
    GameScreen(ScreenStateManager& context, GameLevel* gameLevel);
    ~GameScreen();
    void update(double deltaTime) override;
    void update(const KeyEvent& event) override;
};

#endif //PROJECT_SWA_GAMESCREEN_H