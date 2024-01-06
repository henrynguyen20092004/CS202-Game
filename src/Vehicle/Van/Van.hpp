#ifndef VAN_HPP
#define VAN_HPP

#include "../Vehicle.hpp"

class Van : public Vehicle {
   public:
    Van(TextureHolder& textureHolder, Directions::ID direction);

   private:
    Textures::ID getTextureID() const final;
};

#endif
