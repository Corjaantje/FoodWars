#include "../../Headers/AI/ShotTry.h"

ShotTry::ShotTry(double angle, double power) : _angle{angle}, _power{power}, _score{-1}, _xVelocity{0}, _yVelocity{0} {

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

void ShotTry::setXVeloctity(double xVelocity) {
    _xVelocity = xVelocity;
}

void ShotTry::setYVeloctity(double yVelocity) {
    _yVelocity = yVelocity;
}

double ShotTry::getXVelocity() const {
    return _xVelocity;
}

double ShotTry::getYVelocity() const {
    return _yVelocity;
}
