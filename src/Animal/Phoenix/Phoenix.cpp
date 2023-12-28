#include "Phoenix.hpp"

Phoenix::Phoenix(
    TextureHolder& TextureHolder, Textures::ID textureID,
    PowerUpList& powerUpList
)
    : Animal(TextureHolder, textureID, powerUpList, 1, sf::seconds(1.f)) {}

PowerUp::Type Phoenix::getPowerUpType() const {
    return PowerUp::Type::Regenerate;
}

void Phoenix::handlePlayerCollision(Player& player) {
    if (collidePlayer(player)) {
        player.setRegenerate();
        getParent()->detachChild(*this);
    }
}

