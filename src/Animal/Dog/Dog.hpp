#ifndef DOG_HPP
#define DOG_HPP

#include "../Animal.hpp"

class Dog : public Animal {
   public:
    Dog(TextureHolder& textureHolder);

    void handlePlayerCollision(Player& player) override;

   private:
    Textures::ID getTextureID() const final;
};

#endif
