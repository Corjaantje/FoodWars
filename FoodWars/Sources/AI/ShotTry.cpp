#include "../../Headers/AI/ShotTry.h"

ShotTry::ShotTry(double velocityX, double velocityY, double power) : _velocityX{velocityX}, _velocityY{velocityY},
                                                                     _power{power} {

}

ShotTry::ShotTry() : ShotTry(0, 0, 0) {

}

void ShotTry::setScore(double score) {
    _score = score;
}

double ShotTry::getScore() const {
    return _score;
}