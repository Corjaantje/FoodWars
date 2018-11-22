#ifndef PROJECT_SWA_MAINMENUSCREEN_H
#define PROJECT_SWA_MAINMENUSCREEN_H

#include "IScreen.h"
#include "GameScreen.h"
#include "LevelCreationScreen.h"
#include "LevelSelectionScreen.h"
#include "SettingsScreen.h"
#include "../../../TonicEngine/Headers/Events/MouseEvent.h"
#include "../../../TonicEngine/Headers/Input/IObserver.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/TextButton.h"
#include "../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"
#include "../../../TonicEngine/Headers/Storage/AdvertisingManager.h"

class MainMenuScreen : public IScreen, public IObserver<KeyEvent> {
private:
    void quitGame();
    const AdvertisingManager* advertisingManager;
    SpriteButton* advertisement;
public:
    explicit MainMenuScreen(std::shared_ptr<ScreenStateManager> context, const AdvertisingManager& advertisingManager);
    ~MainMenuScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;
};

#endif //PROJECT_SWA_MAINMENUSCREEN_H
