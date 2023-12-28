#ifndef PHOENIX_HPP
#define PHOENIX_HPP

#include "../Animal.hpp"

class Phoenix : public Animal {
   public:
    Phoenix(
        TextureHolder& TextureHolder, Textures::ID textureID,
        PowerUpList& powerUpList
    );

   private:
    PowerUp::Type getPowerUpType() const override;
    void handlePlayerCollision(Player& player) override;
};

#endif
