#ifndef PROJECT_SWA_SHOTTRY_H
#define PROJECT_SWA_SHOTTRY_H

class ShotTry {
private:
    double _power;
    double _angle;
    double _score;
    double _xVelocity;
    double _yVelocity;
public:
    ShotTry();

    ShotTry(double angle, double power);

    void setXVeloctity(double xVelocity);

    void setYVeloctity(double yVelocity);

    double getXVelocity() const;

    double getYVelocity() const;

    double getAngle() const;

    double getPower() const;

    void setScore(double score);

    double getScore() const;
};

#endif //PROJECT_SWA_SHOTTRY_H
