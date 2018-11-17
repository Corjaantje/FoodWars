#include "../../../Headers/StateMachine/Misc/Coordinate.h"

int Coordinate::getXCoord() const {
    return _xCoord;
}

int Coordinate::getYCoord() const {
    return _yCoord;
}

const void Coordinate::setCoordinates(int x, int y) {
    _xCoord = x;
    _yCoord = y;
}