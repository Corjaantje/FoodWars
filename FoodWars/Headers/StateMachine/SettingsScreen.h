#ifndef PROJECT_SWA_SETTINGSSCREEN_H
#define PROJECT_SWA_SETTINGSSCREEN_H

#include "IScreen.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"

class SettingsScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit SettingsScreen(ScreenStateManager& context);
    ~SettingsScreen();
    void update(double deltaTime) override;
    void update(const KeyEvent& event) override;
private:
    ShapeText* musicVolume = nullptr;
    ShapeText* effectVolume = nullptr;
};

#endif //PROJECT_SWA_SETTINGSSCREEN_H