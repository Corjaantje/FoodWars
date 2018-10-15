
#include "../../Headers/Events/KeyEvent.h"
#include "../../Headers/Input/PrintKeyInputObserver.h"

PrintKeyInputObserver::~PrintKeyInputObserver() = default;

void PrintKeyInputObserver::update(std::shared_ptr<KeyEvent> event) {
    std::cout << "Key event: " << (event->getKey() == KEY::KEY_W ?  "W" : "Geen w") << std::endl;
}

PrintKeyInputObserver::PrintKeyInputObserver() : IObserver() {

}
