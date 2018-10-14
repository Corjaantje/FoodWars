//
// Created by Lucas on 11/10/2018.
//

#ifndef PROJECT_SWA_SCREENSTATE_H
#define PROJECT_SWA_SCREENSTATE_H

#include <tr1/memory>
#include <vector>
#include <iostream>
#include "ScreenPtr.h"
#include <typeinfo>
#include <map>
#include "../../TonicEngine/Facades/IFacade.h"
#include "../../TonicEngine/Headers/Visual/VisualFacade.h"
#include "../../TonicEngine/Headers/Audio/AudioFacade.h"

class ScreenState {
private:
    ScreenPtr _currentState;
    std::map<std::string, IFacade*> _facades;
public:
    ScreenState();
    ScreenPtr* getCurrentState();
    void setState(ScreenPtr screen);
    void setState(IScreen* screen);

    template<typename Facade, typename std::enable_if<std::is_base_of<IFacade, Facade>::value>::type* = nullptr>
    void addFacade(Facade* facade) {
        _facades[typeid(Facade).name()] = facade;
    }

    template<typename Facade, typename std::enable_if<std::is_base_of<IFacade, Facade>::value>::type* = nullptr>
    std::unique_ptr<Facade> getFacade() {
        std::string facadeName = typeid(Facade).name();
        if(_facades.count(facadeName) > 0){
            return std::unique_ptr<Facade>(static_cast<Facade*>(_facades[facadeName])) ;
        }
        return std::unique_ptr<Facade>(nullptr);
    }
};

#endif //PROJECT_SWA_SCREENSTATE_H
