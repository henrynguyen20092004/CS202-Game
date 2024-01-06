#ifndef CAT_HPP
#define CAT_HPP

#include "../../Score/Score.hpp"
#include "../Animal.hpp"

class Cat : public Animal {
   public:
    Cat(TextureHolder& textureHolder, Score* score);

    void handlePlayerCollision(Player& player) override;

   private:
    Score* mScore;

    Textures::ID getTextureID() const final;
};

#endif
