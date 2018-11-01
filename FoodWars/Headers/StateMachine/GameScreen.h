#ifndef PROJECT_SWA_GAMESCREEN_H
#define PROJECT_SWA_GAMESCREEN_H

#include "IScreen.h"
#include "../../../TonicEngine/Headers/Visual/VisualFacade.h"
#include "../../../TonicEngine/Headers/Visual/Renderlist.h"
#include "ScreenStateManager.h"
#include "../GameECS/Systems/DrawSystem.h"
#include "../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../GameECS/Systems/MoveSystem.h"
#include "../GameECS/Systems/TurnSystem.h"
#include "../GameECS/Systems/GravitySystem.h"

class GameScreen : public IScreen, public IObserver<KeyEvent> {
private:
    std::shared_ptr<EntityManager> _entityManager;
    std::shared_ptr<VisualFacade> _visualFacade;
    std::vector<std::shared_ptr<IBaseSystem>> _systems;
    std::shared_ptr<AudioFacade> _audioFacade;
    Renderlist _renderList;
public:
    explicit GameScreen(std::shared_ptr<ScreenStateManager> context);
    ~GameScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;
};


#endif //PROJECT_SWA_GAMESCREEN_H
