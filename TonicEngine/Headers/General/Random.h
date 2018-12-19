#ifndef PROJECT_SWA_RANDOM_H
#define PROJECT_SWA_RANDOM_H

#include <random>
#include <chrono>

class Random {
private:
    std::default_random_engine _generator;

public:
    int between(int min, int max);

    double between(double min, double max);
    explicit Random();
};

#endif //PROJECT_SWA_RANDOM_H
