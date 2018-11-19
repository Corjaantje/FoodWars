#ifndef PROJECT_SWA_DRAWSYSTEM_H
#define PROJECT_SWA_DRAWSYSTEM_H


#include "IBaseSystem.h"
#include "../../../../TonicEngine/Headers/Visual/VisualFacade.h"
#include <chrono>

class DrawSystem : public IBaseSystem {
private:
    std::chrono::duration<double> _timeLast;
    std::shared_ptr<EntityManager> _entityManager;
    std::shared_ptr<VisualFacade> _visualFacade;
    Renderlist _renderList;
    int _updateCallCount;
    std::string _fpsString;

    std::string _playerIcon;
    int _playerUpdateCount = 0;

    bool _showFPS = true;
public:
    DrawSystem(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<VisualFacade> visualFacade);
    ~DrawSystem() override;
    void update(double dt) override;
    bool toggleFpsCounter();
private:
    void drawNonComponents();
    void drawCurrentPlayer();

};


#endif //PROJECT_SWA_DRAWSYSTEM_H
