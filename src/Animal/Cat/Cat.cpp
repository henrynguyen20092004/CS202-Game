#include "Cat.hpp"

#include "../../Player/Player.hpp"

Cat::Cat(TextureHolder& textureHolder, int seasonIndex, Score* score)
    : Animal(textureHolder, Textures::ID::Cat), mScore(score) {
    setHitbox(getLocalBounds());
}

void Cat::handlePlayerCollision(Player& player) {
    if (collidePlayer(player)) {
        mScore->addBonus();
        getParent()->detachChild(*this);
    }
}

Textures::ID Cat::getTextureID() const { return Textures::ID::Cat; }
