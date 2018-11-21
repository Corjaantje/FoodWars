#ifndef PROJECT_SWA_ADVERTISINGSCREEN_H
#define PROJECT_SWA_ADVERTISINGSCREEN_H

#include "IScreen.h"
#include "../GameECS/Systems/IBaseSystem.h"
#include "../../../TonicEngine/Headers/Storage/AdvertisingManager.h"

class AdvertisingScreen : public IScreen, public IObserver<KeyEvent> {
public:
    explicit AdvertisingScreen(std::shared_ptr<ScreenStateManager> context, const AdvertisingManager& manager);
    ~AdvertisingScreen();
    void update(double deltaTime) override;
    void update(std::shared_ptr<KeyEvent> event) override;
private:
    ShapeSprite* shownAD;
    void swapAdvertisement(bool directionNext);
    int currentIndex;
    const AdvertisingManager* _advertisingManager;
};

#endif //PROJECT_SWA_ADVERTISINGSCREEN_H
