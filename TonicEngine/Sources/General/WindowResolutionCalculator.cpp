#include "../../Headers/General/WindowResolutionCalculator.h"

WindowResolutionCalculator::WindowResolutionCalculator() {

}

void WindowResolutionCalculator::setResolution(int width, int height) {
    _windowWidth = width;
    _windowHeight = height;
}

int WindowResolutionCalculator::getConvertedHeight(int height) {
    return static_cast<int>(height * (_windowHeight / DEFAULT_HEIGHT) + 1);
}

int WindowResolutionCalculator::getConvertedWidth(int width) {
    return static_cast<int>(width * (_windowWidth / DEFAULT_WIDTH) + 1);

}

int WindowResolutionCalculator::getConvertedxPos(int xPos) {
    return static_cast<int>(xPos * (_windowWidth / DEFAULT_WIDTH));
}

int WindowResolutionCalculator::getConvertedyPos(int yPos) {
    return static_cast<int>(yPos * (_windowHeight / DEFAULT_HEIGHT));

}
