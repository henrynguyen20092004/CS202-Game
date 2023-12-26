#ifndef ELEPHANT_HPP
#define ELEPHANT_HPP

#include "../Animal.hpp"

class Elephant : public Animal {
   public:
    Elephant(
        TextureHolder& texture, Textures::ID textureID, PowerUpList& powerUpList
    );

   private:
    void onPlayerCollision(Player& player) override;
};

#endif
