#include "../../Headers/AI/ShootingSimulatorConfig.h"

ShootingSimulatorConfig::ShootingSimulatorConfig(double angleIncrease, double powerIncrease) : _angleIncrease{
        angleIncrease}, _powerIncrease{powerIncrease} {

}

ShootingSimulatorConfig::ShootingSimulatorConfig(double minAngle, double angleIncrease, double minPower,
                                                 double powerIncrease) : _maxAngle{minAngle},
                                                                         _angleIncrease{angleIncrease},
                                                                         _minPower{minPower},
                                                                         _powerIncrease{powerIncrease} {

}

double ShootingSimulatorConfig::getMinPower() const {
    return _minPower;
}

double ShootingSimulatorConfig::getMaxPower() const {
    return _maxPower;
}

double ShootingSimulatorConfig::getPowerIncrease() const {
    return _powerIncrease;
}

double ShootingSimulatorConfig::getMinAngle() const {
    return _minAngle;
}

double ShootingSimulatorConfig::getMaxAngle() const {
    return _maxAngle;
}

double ShootingSimulatorConfig::getAngleIncrease() const {
    return _angleIncrease;
}