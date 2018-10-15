#ifndef PROJECT_SWA_GAMESCREEN_H
#define PROJECT_SWA_GAMESCREEN_H


#include "IScreen.h"
#include "../../../TonicEngine/Headers/Visual/VisualFacade.h"
#include "../../../TonicEngine/Headers/Visual/Renderlist.h"
#include "ScreenStateManager.h"
#include "../GameECS/Systems/DrawSystem.h"

class GameScreen : public IScreen {
private:
    std::shared_ptr<VisualFacade> _visualFacade;
    EntityManager _entityManager;
    DrawSystem _drawSystem;
    Renderlist _renderList;
public:
    explicit GameScreen(std::shared_ptr<ScreenStateManager> context);
    ~GameScreen();
    void update(double deltaTime);
};


#endif //PROJECT_SWA_GAMESCREEN_H
