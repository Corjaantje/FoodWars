#include "../../Headers/Input/PrintWindowObserver.h"

PrintWindowObserver::~PrintWindowObserver() = default;

void PrintWindowObserver::update(std::shared_ptr<WindowEvent> event) {
    std::cout << "New Screen Width: " << (event->getWidth()) << " New Screen Height: " << (event->getHeight()) << std::endl;
}

PrintWindowObserver::PrintWindowObserver() : IObserver() {

}