#ifndef PROJECT_SWA_HIGHSCORESCREEN_H
#define PROJECT_SWA_HIGHSCORESCREEN_H

#include "IScreen.h"
#include "ScreenStateManager.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/Button.h"

class HighscoreScreen : public IScreen, public IObserver<KeyEvent> {
private:
    std::shared_ptr<VisualFacade> visualFacade;
    std::shared_ptr<AudioFacade> audioFacade;
    Renderlist _renderList;
    std::vector<Button*> _buttons;
public:
    explicit HighscoreScreen(std::shared_ptr<ScreenStateManager> context);
    ~HighscoreScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;
};


#endif //PROJECT_SWA_HIGHSCORESCREEN_H
