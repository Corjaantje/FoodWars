#ifndef PROJECT_SWA_DRAWSYSTEM_H
#define PROJECT_SWA_DRAWSYSTEM_H


#include "IBaseSystem.h"
#include "../../../../TonicEngine/Headers/Visual/VisualFacade.h"
#include "../../../../TonicEngine/Headers/Input/InputFacade.h"
#include "../../StateMachine/Misc/WeaponSelection.h"
#include "../../../../TonicEngine/Headers/Visual/Shapes/SpriteButton.h"
#include <chrono>

class DrawSystem : public IBaseSystem {
private:
    std::chrono::duration<double> _timeLast;
    std::vector<IShape *> _sprites;
    std::vector<IShape *> _shapes;
    VisualFacade* _visualFacade;
    InputFacade* _inputFacade;
    EntityManager *_entityManager;
    Renderlist _renderList;
    int _updateCallCount;
    std::string _fpsString;

    std::string _playerIconOne;
    std::string _playerIconTwo;
    int _playerUpdateCount = 0;

    WeaponSelection _weaponSelection;

    bool _showFPS = true;
public:
    DrawSystem(EntityManager &entityManager, VisualFacade& visualFacade, InputFacade& inputFacade);
    ~DrawSystem() override;
    void update(double dt) override;
    bool toggleFpsCounter();
    void addShape(IShape* shape);
private:
    void drawNonComponents();
    void drawPlayers();
    void drawPlayerStats();
    void drawWeaponSelection(int x, int playerId, std::string selection);
    Colour getConvertedHealthColor(int health);

    template<typename T, typename... Args>
    IShape *createShape(Args &&... args) {
        T *shape = new T(std::forward<Args>(args)...);
        _sprites.push_back(shape);
        return shape;
    }
};


#endif //PROJECT_SWA_DRAWSYSTEM_H
