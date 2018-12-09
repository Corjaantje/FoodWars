#ifndef PROJECT_SWA_ADVERTISINGSCREEN_H
#define PROJECT_SWA_ADVERTISINGSCREEN_H

#include "IScreen.h"
#include "../GameECS/Systems/IBaseSystem.h"
#include "../../../TonicEngine/Headers/Storage/FileManager.h"

class AdvertisingScreen : public IScreen, public IObserver<KeyEvent> {
public:
    AdvertisingScreen(ScreenStateManager& context);
    void update(double deltaTime) override;
    void update(const KeyEvent& event) override;
private:
    ShapeSprite* _shownAD;
    std::string _currentAD;
    std::vector<std::string> _advertisements;
    void swapAdvertisement(bool directionNext);
    int _currentIndex;
    const FileManager _fileManager;
};

#endif //PROJECT_SWA_ADVERTISINGSCREEN_H
