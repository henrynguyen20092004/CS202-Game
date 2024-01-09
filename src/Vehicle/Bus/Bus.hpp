#ifndef BUS_HPP
#define BUS_HPP

#include "../Vehicle.hpp"

class Bus : public Vehicle {
   public:
    Bus(TextureHolder& textureHolder, int seasonIndex,
        Directions::ID direction);

   private:
    Textures::ID getTextureID() const final;
};

#endif
