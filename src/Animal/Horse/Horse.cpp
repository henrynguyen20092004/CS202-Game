#include "Horse.hpp"

#include "../../Player/Player.hpp"

Horse::Horse(TextureHolder& textureHolder, const std::vector<PowerUpList*>& powerUpList)
    : Animal(textureHolder, Textures::ID::Horse), mPowerUpList(powerUpList) {
    setHitbox(getLocalBounds());
}

void Horse::handlePlayerCollision(Player& player) {
    if (collidePlayer(player)) {
        mPowerUpList[player.getPlayerNumber()]->addPowerUp(
            PowerUp::Type::Immortality
        );
        getParent()->detachChild(*this);
    }
}

Textures::ID Horse::getTextureID() const { return Textures::ID::Horse; }
