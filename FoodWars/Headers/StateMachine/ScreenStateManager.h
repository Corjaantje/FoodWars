#ifndef PROJECT_SWA_SCREENSTATE_H
#define PROJECT_SWA_SCREENSTATE_H

#include "memory"
#include <vector>
#include <iostream>
#include <typeinfo>
#include <map>
#include "../../../TonicEngine/Facades/IFacade.h"
#include "../../../TonicEngine/Headers/Visual/VisualFacade.h"
#include "../../../TonicEngine/Headers/Audio/AudioFacade.h"
#include "../LevelManager.h"

class IScreen;

class ScreenStateManager {
private:
    IScreen* _currentState;
    std::map<std::string, IFacade*> _facades;
    std::map<std::string, std::unique_ptr<IScreen>> _screenStates;

    LevelManager* _levelManager;
    const WindowResolutionCalculator* _windowResCalc;
    double timeModifier = 1.0;
public:
    ScreenStateManager();
    ~ScreenStateManager();

    IScreen& getCurrentState() const;
    double getTimeModifier() const;
    const WindowResolutionCalculator& getWindowResolutionCalculator() const;
    LevelManager& getLevelManager() const;

    void setTimeModifier(double timeModifier);
    void setLevelManager(LevelManager& levelManager);
    void setWindowResolutionCalculator(const WindowResolutionCalculator& windowResCalc);

    template<typename Screen, typename std::enable_if<std::is_base_of<IScreen, Screen>::value>::type * = nullptr>
    void addOrSetScreenState(std::unique_ptr<Screen> screen){
        _screenStates[typeid(Screen).name()] = std::move(screen);
    }

    template<typename Screen, typename std::enable_if<std::is_base_of<IScreen, Screen>::value>::type * = nullptr>
    void setActiveScreen(std::unique_ptr<Screen> screen) {
        std::string screenName = typeid(Screen).name();
        addOrSetScreenState(std::move(screen));
        _currentState = _screenStates[screenName].get();
    }

    template<typename Screen, typename std::enable_if<std::is_base_of<IScreen, Screen>::value>::type* = nullptr>
    void createOrSetActiveScreen() {
        std::string screenName = typeid(Screen).name();
        if(_screenStates.count(screenName) <= 0){
            _screenStates[screenName] = std::make_unique<Screen>(*this);
        }
        _currentState = _screenStates[screenName].get();
    }

    template<typename Screen, typename std::enable_if<std::is_base_of<IScreen, Screen>::value>::type * = nullptr>
    void setActiveScreen() {
        std::string screenName = typeid(Screen).name();
        if (_screenStates.count(screenName) > 0) _currentState = _screenStates[screenName].get();
    }

    void addFacade(IFacade& facade) {
        _facades[typeid(facade).name()] = &facade;
    }

    template<typename Facade>
    Facade* getFacade() const {
        std::string facadeName = typeid(Facade).name();
        if(_facades.count(facadeName) > 0){
            return static_cast<Facade*>(_facades.at(facadeName));
        }
        return nullptr;
    }
};

#endif //PROJECT_SWA_SCREENSTATE_H
