#ifndef CAT_HPP
#define CAT_HPP

#include "../Animal.hpp"

class Cat : public Animal {
   public:
    Cat(TextureHolder& texture, Textures::ID textureID,
        PowerUpList& powerUpList);

    void handlePlayerCollision(Player& player) override;
};

#endif
