#ifndef PROJECT_SWA_SHOTTRY_H
#define PROJECT_SWA_SHOTTRY_H

class ShotTry {
private:
    double _power;
    double _angle;
    double _score;
public:
    ShotTry();

    ShotTry(double angle, double power);

    double getAngle() const;

    double getPower() const;

    void setScore(double score);

    double getScore() const;
};

#endif //PROJECT_SWA_SHOTTRY_H
