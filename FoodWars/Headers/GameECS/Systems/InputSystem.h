
#include "IBaseSystem.h"
#include "../../../../TonicEngine/Headers/Events/KeyEvent.h"
#include "../../../../TonicEngine/Headers/Input/InputFacade.h"

class InputSystem: public IBaseSystem, public IObserver<KeyEvent> {
private:
    std::shared_ptr<EntityManager> _entityManager;
    std::shared_ptr<InputFacade> _inputFacade;
public:
    InputSystem(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<InputFacade> inputFacade);
    ~InputSystem() override;
    void update(double dt) override;
    void update(std::shared_ptr<KeyEvent> event) override;
};