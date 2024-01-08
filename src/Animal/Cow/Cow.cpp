#include "Cow.hpp"

#include "../../Player/Player.hpp"

Cow::Cow(
    TextureHolder& textureHolder, std::vector<PowerUpList*> powerUpList
)
    : Animal(textureHolder, Textures::ID::Cow),
      mPowerUpList(powerUpList) {
    setHitbox(getLocalBounds());  // TODO: Set hitbox properly
}

void Cow::handlePlayerCollision(Player& player) {
    if (collidePlayer(player)) {
        mPowerUpList[player.getPlayerNumber()]->addPowerUp(
            PowerUp::Type::SlowTime
        );
        getParent()->detachChild(*this);
    }
}