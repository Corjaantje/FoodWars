#include "../../Headers/General/WindowResolutionCalculator.h"

WindowResolutionCalculator::WindowResolutionCalculator() {

}

void WindowResolutionCalculator::setResolution(int width, int height) {
    _windowWidth = width;
    _windowHeight = height;
}

int WindowResolutionCalculator::getConvertedHeight(int height) {
    return height * (_windowHeight / DEFAULT_HEIGHT) + 1;
}

int WindowResolutionCalculator::getConvertedWidth(int width) {
    return width * (_windowWidth / DEFAULT_WIDTH) + 1;

}

int WindowResolutionCalculator::getConvertedxPos(int xPos) {
    return xPos * (_windowWidth / DEFAULT_WIDTH);
}

int WindowResolutionCalculator::getConvertedyPos(int yPos) {
    return yPos * (_windowHeight / DEFAULT_HEIGHT);

}
