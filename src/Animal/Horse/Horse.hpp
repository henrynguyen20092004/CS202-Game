#ifndef HORSE_HPP
#define HORSE_HPP

#include "../../PowerUpList/PowerUpList.hpp"
#include "../Animal.hpp"

class Horse : public Animal {
   public:
    Horse(TextureHolder& textureHolder, const std::vector<PowerUpList*>& powerUpList);

    void handlePlayerCollision(Player& player) override;

   private:
    std::vector<PowerUpList*> mPowerUpList;

    Textures::ID getTextureID() const final;
};

#endif
