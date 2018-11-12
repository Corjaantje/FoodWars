#ifndef PROJECT_SWA_SETTINGSSCREEN_H
#define PROJECT_SWA_SETTINGSSCREEN_H

#include "IScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"

class SettingsScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit SettingsScreen(std::shared_ptr<ScreenStateManager> context);
    ~SettingsScreen() override;
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;
private:
    ShapeText* musicVolume = nullptr;
    ShapeText* effectVolume = nullptr;
};

#endif //PROJECT_SWA_SETTINGSSCREEN_H