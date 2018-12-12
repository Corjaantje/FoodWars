#include <time.h>
#include "../../Headers/General/Random.h"

Random::Random() : _generator(std::chrono::system_clock::now().time_since_epoch().count()) {
}

int Random::between(int min, int max) {
    std::uniform_int_distribution<int> distribution{min, max};
    return distribution(_generator);
}