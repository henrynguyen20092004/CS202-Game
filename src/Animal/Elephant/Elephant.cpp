#include "Elephant.hpp"

Elephant::Elephant(
    TextureHolder& textureHolder, Textures::ID textureID,
    PowerUpList& powerUpList
)
    : Animal(textureHolder, textureID, powerUpList, 10, sf::seconds(2.f)) {
    setHitbox(getLocalBounds());  // TODO: Set hitbox properly
}

void Elephant::handlePlayerCollision(Player& player) {
    if (collidePlayer(player)) {
        player.heal();
        getParent()->detachChild(*this);
    }
}

PowerUp::Type Elephant::getPowerUpType() const { return PowerUp::Type::Heal; }
