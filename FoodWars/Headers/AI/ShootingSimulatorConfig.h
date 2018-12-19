#ifndef FOODWARS_SHOOTINGSIMULATORCONFIG_H
#define FOODWARS_SHOOTINGSIMULATORCONFIG_H

class ShootingSimulatorConfig {
private:
    double _powerIncrease = 10;
    double _minPower = 10;
    double _maxPower = 50;

    double _minAngle = 0;
    double _maxAngle = 135;
    double _angleIncrease = 5;
public:
    ShootingSimulatorConfig() = default;

    ShootingSimulatorConfig(double angleIncrease, double powerIncrease);

    ShootingSimulatorConfig(double minAngle, double angleIncrease, double minPower, double powerIncrease);

    double getMinPower() const;

    double getMaxPower() const;

    double getPowerIncrease() const;

    double getMinAngle() const;

    double getMaxAngle() const;

    double getAngleIncrease() const;
};

#endif //FOODWARS_SHOOTINGSIMULATORCONFIG_H
