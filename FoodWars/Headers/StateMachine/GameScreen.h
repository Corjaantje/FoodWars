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

class GameScreen : public IScreen {
private:
    std::shared_ptr<EntityManager> _entityManager;
    std::shared_ptr<VisualFacade> _visualFacade;
    std::shared_ptr<InputFacade> _inputFacade;
    std::vector<IBaseSystem> systems;
    DrawSystem _drawSystem;
    MoveSystem _moveSystem;
    TurnSystem _turnSystem;
    GravitySystem _gravitySystem;
    Renderlist _renderList;
public:
    explicit GameScreen(std::shared_ptr<ScreenStateManager> context);
    ~GameScreen();
    void update(double deltaTime) override;
};


#endif //PROJECT_SWA_GAMESCREEN_H
