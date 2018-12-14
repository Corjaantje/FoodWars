#ifndef PROJECT_SWA_SHOTTRY_H
#define PROJECT_SWA_SHOTTRY_H

class ShotTry {
private:
    double _power;
    double _velocityX;
    double _velocityY;
    double _score;
public:
    ShotTry();

    ShotTry(double velocityX, double velocityY, double power);

    void setScore(double score);

    double getScore() const;
};

#endif //PROJECT_SWA_SHOTTRY_H
