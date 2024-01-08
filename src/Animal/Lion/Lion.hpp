#ifndef LION_HPP
#define LION_HPP

#include "../Animal.hpp"

class Lion : public Animal {
   public:
    Lion(TextureHolder& textureHolder);

    void handlePlayerCollision(Player& player) override;
};

#endif
