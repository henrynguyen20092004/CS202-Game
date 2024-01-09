#ifndef CAR_HPP
#define CAR_HPP

#include "../Vehicle.hpp"

class Car : public Vehicle {
   public:
    Car(TextureHolder& textureHolder, int seasonIndex,
        Directions::ID direction);

   private:
    Textures::ID getTextureID() const final;
};

#endif
