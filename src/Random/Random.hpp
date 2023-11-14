#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <time.h>

#include <random>

class Random {
   public:
    Random(int seed = time(nullptr));

    int getIntInRange(int min, int max);
    float getFloatInRange(float min, float max);

   private:
    std::mt19937 mEngine;
};

#endif  // RANDOM_HPP
