#include "Cat.hpp"

Cat::Cat(
    TextureHolder& textureHolder, Textures::ID textureID,
    PowerUpList& powerUpList
)
    : Animal(textureHolder, textureID, powerUpList, 6, sf::seconds(2.f)) {
    setHitbox(getLocalBounds());  // TODO: Set hitbox properly
}

void Cat::handlePlayerCollision(Player& player) {
    if (collidePlayer(player)) {
        player.addBonusScore();
        getParent()->detachChild(*this);
    }
}
