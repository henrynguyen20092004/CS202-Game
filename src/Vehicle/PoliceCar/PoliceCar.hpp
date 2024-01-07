#ifndef POLICE_CAR_HPP
#define POLICE_CAR_HPP

#include "../Vehicle.hpp"

class PoliceCar : public Vehicle {
   public:
    PoliceCar(TextureHolder& textureHolder, Directions::ID direction);
};

#endif
