#ifndef PROJECT_SWA_DRAWSYSTEM_H
#define PROJECT_SWA_DRAWSYSTEM_H


#include "IBaseSystem.h"
#include "../../../../TonicEngine/Headers/Visual/VisualFacade.h"
#include "../../../../TonicEngine/Headers/Input/InputFacade.h"
#include <chrono>

class DrawSystem : public IBaseSystem {
private:
    std::chrono::duration<double> _timeLast;
    std::vector<IShape *> _sprites;
    VisualFacade* _visualFacade;
    EntityManager *_entityManager;
    Renderlist _renderList;
    int _updateCallCount;
    std::string _fpsString;

    std::string _playerIconOne;
    std::string _playerIconTwo;
    int _playerUpdateCount = 0;

    bool _showFPS = true;
public:
    DrawSystem(EntityManager &entityManager, VisualFacade& visualFacade);
    ~DrawSystem() override;
    void update(double dt) override;
    bool toggleFpsCounter();

private:
    void drawNonComponents();
    void drawPlayers();
    void drawPlayerStats();
    Colour getConvertedHealthColor(int health);

    template<typename T, typename... Args>
    IShape *createShape(Args &&... args) {
        T *shape = new T(std::forward<Args>(args)...);
        _sprites.push_back(shape);
        return shape;
    }
};


#endif //PROJECT_SWA_DRAWSYSTEM_H
