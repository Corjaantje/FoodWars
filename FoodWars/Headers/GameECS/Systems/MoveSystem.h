

#ifndef PROJECT_SWA_MOVESYSTEM_H
#define PROJECT_SWA_MOVESYSTEM_H

#include "IBaseSystem.h"
#include "../../../../TonicEngine/Headers/Input/InputFacade.h"

class MoveSystem : public IBaseSystem, public IObserver<KeyEvent> {
private:
    std::shared_ptr<EntityManager> _entityManager;
public:
    MoveSystem(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<InputFacade> inputFacade);
    ~MoveSystem() override;
    void update(double dt) override;
    void update(std::shared_ptr<KeyEvent> event) override;
};

#endif //PROJECT_SWA_MOVESYSTEM_H
