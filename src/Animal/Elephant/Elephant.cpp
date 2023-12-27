#include "Elephant.hpp"

Elephant::Elephant(
    TextureHolder& textureHolder, Textures::ID textureID,
    PowerUpList& powerUpList
)
    : Animal(textureHolder, textureID, powerUpList, 10, sf::seconds(2.f)) {}

void Elephant::onPlayerCollision(Player& player) {
    player.heal();
    getParent()->detachChild(*this);
}
