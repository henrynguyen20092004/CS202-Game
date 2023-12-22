#ifndef POLAR_BEAR_HPP
#define POLAR_BEAR_HPP

#include "../Animal.hpp"

class PolarBear : public Animal {
   public:
    PolarBear(
        TextureHolder& TextureHolder, Textures::ID textureID,
        PowerUpList& powerUpList
    );

   private:
    PowerUp::Type getPowerUpType() const override;
};

#endif
