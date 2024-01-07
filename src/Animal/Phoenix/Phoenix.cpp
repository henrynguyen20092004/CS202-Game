#include "Phoenix.hpp"

Phoenix::Phoenix(
    TextureHolder& TextureHolder, Textures::ID textureID,
    PowerUpList& powerUpList
)
    : Animal(TextureHolder, textureID, powerUpList, 1, sf::seconds(1.f)) {}

void Phoenix::handlePlayerCollision(Player& player) {
    if (collidePlayer(player)) {
        player.addRegenerate();
        getParent()->detachChild(*this);
    }
}
