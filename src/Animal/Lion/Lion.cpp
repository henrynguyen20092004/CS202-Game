#include "Lion.hpp"

#include "../../Player/Player.hpp"

Lion::Lion(TextureHolder& textureHolder)
    : Animal(textureHolder, Textures::ID::Lion) {
    setHitbox(getLocalBounds());  // TODO: Set hitbox properly
}

void Lion::handlePlayerCollision(Player& player) {
    if (collidePlayer(player)) {
        player.addRevival();
        getParent()->detachChild(*this);
    }
}

Textures::ID Lion::getTextureID() const { return Textures::ID::Lion; }
