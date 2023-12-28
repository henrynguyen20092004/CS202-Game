#ifndef CAR_HPP
#define CAR_HPP

#include "../Vehicle.hpp"

class Car : public Vehicle{
   public:
    Car(TextureHolder& textureHolder, Directions::ID direction);
};

#endif
