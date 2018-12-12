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

void Coordinate::accept(SerializationVisitor &visitor) {
    visitor.visit("x", _xCoord);
    visitor.visit("y", _yCoord);
}

std::string Coordinate::getName() const {
    return "Coordinate";
}
