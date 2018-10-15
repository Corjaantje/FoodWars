#include "../../Headers/Input/PrintMouseInputObserver.h"

PrintMouseInputObserver::~PrintMouseInputObserver() = default;

void PrintMouseInputObserver::update(std::shared_ptr<MouseEvent> event) {
    std::cout << "Screen X Position: " << (event->getXPosition()) << " Screen Y Position: " << (event->getYPosition()) << std::endl;
}

PrintMouseInputObserver::PrintMouseInputObserver() : IObserver() {

}