#include "../../Headers/General/WindowResolutionCalculator.h"

WindowResolutionCalculator::WindowResolutionCalculator() {

}

void WindowResolutionCalculator::setResolution(int width, int height) {
    _windowWidth = width;
    _windowHeight = height;
}

int WindowResolutionCalculator::getConvertedHeightDraw(int height) const {
    return static_cast<int>(height * (_windowHeight / DEFAULT_HEIGHT) + 1);
}

int WindowResolutionCalculator::getConvertedWidthDraw(int width) const {
    return static_cast<int>(width * (_windowWidth / DEFAULT_WIDTH) + 1);

}

int WindowResolutionCalculator::getConvertedxPosDraw(int xPos) const {
    return static_cast<int>(xPos * (_windowWidth / DEFAULT_WIDTH));
}

int WindowResolutionCalculator::getConvertedyPosDraw(int yPos) const {
    return static_cast<int>(yPos * (_windowHeight / DEFAULT_HEIGHT));
}

int WindowResolutionCalculator::getConvertedxPosClick(int xPos) const {
    return static_cast<int>(xPos * (DEFAULT_WIDTH / _windowWidth));
}

int WindowResolutionCalculator::getConvertedyPosClick(int yPos) const {
    return static_cast<int>(yPos * (DEFAULT_HEIGHT / _windowHeight));

}
