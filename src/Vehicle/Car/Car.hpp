#ifndef CAR_HPP
#define CAR_HPP

#include "../../ResourceHolder/ResourceHolder.hpp"
#include "../Vehicle.hpp"

class Car : public Vehicle {
   public:
    Car(Directions::ID direction, float speed, TextureHolder& textureHolder);
};

#endif  // CAR_HPP
