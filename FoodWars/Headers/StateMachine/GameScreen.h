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
    std::unique_ptr<GameLevel> _gameLevel;
    EntityManager *_entityManager;

    std::shared_ptr<AudioFacade> _audioFacade;
    std::shared_ptr<VisualFacade> _visualFacade;
    std::vector<std::unique_ptr<IBaseSystem>> _systems;
    DrawSystem* drawSystem = nullptr;
    AnimationManager* _animationManager;
    ShootingSystem* _shootingSystem = nullptr;
    StorageSystem* _storage;
    int playerOne;
    int playerTwo;
public:
    explicit GameScreen(const std::shared_ptr<ScreenStateManager> &context, std::unique_ptr<GameLevel> &gameLevel);
    ~GameScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;
    void addBackground();
};

#endif //PROJECT_SWA_GAMESCREEN_H