
#include "../../Headers/Events/KeyEvent.h"
#include "../../Headers/Input/PrintKeyInputObserver.h"

PrintKeyInputObserver::~PrintKeyInputObserver() = default;

void PrintKeyInputObserver::update(KeyEvent& event) {
    std::cout << "Key event: " << (event.getKey() == KEY::KEY_W ?  "W" : "Geen w") << std::endl;
}

PrintKeyInputObserver::PrintKeyInputObserver() : IObserver() {

}
