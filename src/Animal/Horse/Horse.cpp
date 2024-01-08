#include "Horse.hpp"

#include "../../Player/Player.hpp"

Horse::Horse(TextureHolder& textureHolder, std::vector<PowerUpList*> powerUpList)
    : Animal(textureHolder, Textures::ID::Horse), mPowerUpList(powerUpList) {
    setHitbox(getLocalBounds());  // TODO: Set hitbox properly
}

void Horse::handlePlayerCollision(Player& player) {
    if (collidePlayer(player)) {
        mPowerUpList[player.getPlayerNumber()]->addPowerUp(
            PowerUp::Type::Immortality
        );
        getParent()->detachChild(*this);
    }
}