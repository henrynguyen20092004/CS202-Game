#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <time.h>

#include <random>
#include <vector>

template <typename T>
class Random {
   public:
    static T generate(T min, T max);
    static T generate(const std::vector<T>& list);

   private:
    static std::mt19937 mEngine;
};

template <typename T>
std::mt19937 Random<T>::mEngine(time(nullptr));

#include "Random.inl"

#endif
