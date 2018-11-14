#ifndef PROJECT_SWA_GAMESCREEN_H
#define PROJECT_SWA_GAMESCREEN_H

#include "IScreen.h"
#include "../GameECS/Systems/DrawSystem.h"
#include "../GameECS/Systems/MoveSystem.h"
#include "../GameECS/Systems/TurnSystem.h"
#include "../GameECS/Systems/GravitySystem.h"
#include "../GameECS/Systems/StorageSystem.h"

class GameScreen : public IScreen, public IObserver<KeyEvent> {
private:
    std::shared_ptr<EntityManager> _entityManager;
    std::vector<IBaseSystem*> _systems;
    StorageSystem* _storage;
public:
    explicit GameScreen(const std::shared_ptr<ScreenStateManager>& context, EntityManager entityManager);
    ~GameScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;
};


#endif //PROJECT_SWA_GAMESCREEN_H
