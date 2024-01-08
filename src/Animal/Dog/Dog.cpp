#include "Dog.hpp"

#include "../../Player/Player.hpp"

Dog::Dog(TextureHolder& textureHolder)
    : Animal(textureHolder, Textures::ID::Dog) {
    setHitbox(getLocalBounds());  // TODO: Set hitbox properly
}

void Dog::handlePlayerCollision(Player& player) {
    if (collidePlayer(player)) {
        player.addHealth();
        getParent()->detachChild(*this);
    }
}
