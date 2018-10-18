#pragma once
#ifndef PROJECT_SWA_GAMESCREEN_H
#define PROJECT_SWA_GAMESCREEN_H

#include "IScreen.h"
#include "../../../TonicEngine/Headers/Visual/VisualFacade.h"
#include "../../../TonicEngine/Headers/Visual/Renderlist.h"
#include "ScreenStateManager.h"
#include "../GameECS/Systems/DrawSystem.h"
#include "../GameECS/Systems/InputSystem.h"
#include "MainMenuScreen.h"

class GameScreen : public IScreen, public IObserver<KeyEvent> {
private:
    std::shared_ptr<EntityManager> _entityManager;
    std::shared_ptr<VisualFacade> _visualFacade;
    std::shared_ptr<AudioFacade> _audioFacade;
    std::shared_ptr<InputFacade> _inputFacade;
    DrawSystem _drawSystem;
    std::shared_ptr<InputSystem> _inputSystem;
    Renderlist _renderList;
public:
    explicit GameScreen(std::shared_ptr<ScreenStateManager> context);
    ~GameScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;
};


#endif //PROJECT_SWA_GAMESCREEN_H
