#ifndef PROJECT_SWA_CREDITSCREEN_H
#define PROJECT_SWA_CREDITSCREEN_H

#include "IScreen.h"
#include "ScreenStateManager.h"
#include "../../../TonicEngine/Headers/Events/KeyEvent.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/Button.h"
#include "../../../TonicEngine/Headers/Visual/VisualFacade.h"
#include "../../../TonicEngine/Headers/Audio/AudioFacade.h"
#include "../../Headers/StateMachine/MainMenuScreen.h"
#include <memory>

class CreditScreen : public IScreen, public IObserver<KeyEvent> {
private:
    std::shared_ptr<VisualFacade> visualFacade;
    std::shared_ptr<AudioFacade> audioFacade;
    Renderlist _renderList;
    std::vector<Button*> _buttons;
public:
    CreditScreen(std::shared_ptr<ScreenStateManager> context);
    ~CreditScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;
};

#endif //PROJECT_SWA_CREDITSCREEN_H
