#ifndef LION_HPP
#define LION_HPP

#include "../Animal.hpp"

class Lion : public Animal {
   public:
    Lion(TextureHolder& textureHolder, int seasonIndex);

    void handlePlayerCollision(Player& player) override;

   private:
    Textures::ID getTextureID() const final;
};

#endif
