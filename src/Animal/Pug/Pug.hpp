#ifndef PUG_HPP
#define PUG_HPP

#include "../Animal.hpp"

class Pug : public Animal {
   public:
    Pug(TextureHolder& textureHolder, Textures::ID textureID,
        PowerUpList& powerUpList);

   private:
    PowerUp::Type getPowerUpType() const override;
};

#endif
