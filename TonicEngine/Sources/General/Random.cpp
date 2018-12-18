#include <time.h>
#include "../../Headers/General/Random.h"

Random::Random() : _generator(static_cast<unsigned int>(std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()).time_since_epoch().count())) {
}

int Random::between(int min, int max) {
    std::uniform_int_distribution<int> distribution{min, max};
    return distribution(_generator);
}

double Random::between(double min, double max) {
    std::uniform_real_distribution<double> distribution{min, max};
    return distribution(_generator);
}
