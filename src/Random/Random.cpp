#include "Random.hpp"

Random::Random(int seed) : mEngine(seed) {}

int Random::getIntInRange(int min, int max) {
    return std::uniform_int_distribution<int>(min, max)(mEngine);
}

float Random::getFloatInRange(float min, float max) {
    return std::uniform_real_distribution<float>(min, max)(mEngine);
}
