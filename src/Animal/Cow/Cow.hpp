#ifndef COW_HPP
#define COW_HPP

#include "../../PowerUpList/PowerUpList.hpp"
#include "../Animal.hpp"

class Cow : public Animal {
   public:
    Cow(TextureHolder& textureHolder, std::vector<PowerUpList*> powerUpList);

    void handlePlayerCollision(Player& player) override;

   private:
    std::vector<PowerUpList*> mPowerUpList;
};

#endif