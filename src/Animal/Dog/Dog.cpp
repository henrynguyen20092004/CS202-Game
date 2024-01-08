#include "Dog.hpp"

#include "../../Player/Player.hpp"

Dog::Dog(TextureHolder& textureHolder)
    : Animal(textureHolder, Textures::ID::Dog) {
    setHitbox(getLocalBounds());
}

void Dog::handlePlayerCollision(Player& player) {
    if (collidePlayer(player)) {
        player.addHealth();
        getParent()->detachChild(*this);
    }
}

Textures::ID Dog::getTextureID() const { return Textures::ID::Dog; }
