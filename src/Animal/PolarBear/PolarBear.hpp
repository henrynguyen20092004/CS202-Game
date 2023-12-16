#ifndef POLAR_BEAR_HPP
#define POLAR_BEAR_HPP

#include "../Animal.hpp"

class PolarBear : public Animal {
   public:
    typedef std::unique_ptr<PolarBear> Ptr;

    PolarBear(
        TextureHolder& TextureHolder, Textures::ID textureID,
        sf::View& worldView, PowerUpList& powerUpList
    );

   private:
    PowerUp::Type getPowerUpType() const override;
};

#endif
