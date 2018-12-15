#include "../../Headers/AI/ShotTry.h"

ShotTry::ShotTry(double angle, double power) : _angle{angle}, _power{power} {

}

ShotTry::ShotTry() : ShotTry(0, 0) {

}

void ShotTry::setScore(double score) {
    _score = score;
}

double ShotTry::getScore() const {
    return _score;
}

double ShotTry::getAngle() const {
    return _angle;
}

double ShotTry::getPower() const {
    return _power;
}
