#ifndef POLICE_CAR_HPP
#define POLICE_CAR_HPP

#include "../Vehicle.hpp"

class PoliceCar : public Vehicle {
   public:
    PoliceCar(
        TextureHolder& textureHolder, int seasonIndex, Directions::ID direction
    );

   private:
    Textures::ID getTextureID() const final;
};

#endif
