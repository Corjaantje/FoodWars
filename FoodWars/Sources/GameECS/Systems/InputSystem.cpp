#include <utility>
#include "../../../Headers/GameECS/Systems/InputSystem.h"
#include "../../../../TonicEngine/Headers/Input/InputFacade.h"

InputSystem::InputSystem(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<InputFacade> inputFacade) : IBaseSystem(),
    _entityManager(std::move(entityManager)),
    _inputFacade(std::move(inputFacade)) {
}

void InputSystem::update(double dt) const {

}

void InputSystem::update(std::shared_ptr<KeyEvent> event) {
    switch (event->getKey()) {
        case KEY::KEY_W:
            std::cout << "W" << std::endl;
            break;
        case KEY::KEY_A:
            std::cout << "A" << std::endl;
            break;
        case KEY::KEY_D:
            std::cout << "D" << std::endl;
            break;
        case KEY::KEY_S:
            std::cout << "S" << std::endl;
            break;
        default:
            std::cout << "hi" << std::endl;
            break;
    }
}

InputSystem::~InputSystem() {

}
