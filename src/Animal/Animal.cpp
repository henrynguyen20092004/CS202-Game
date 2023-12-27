#include "Animal.hpp"

#include "../Global/Global.hpp"

Animal::Animal(
    TextureHolder& TextureHolder, Textures::ID textureID,
    PowerUpList& powerUpList, int numFrames, sf::Time duration
)
    : SpriteNode(TextureHolder, textureID),
      mAnimation(
          mSprite, sf::Vector2i(Global::TILE_SIZE, Global::TILE_SIZE),
          numFrames, duration, true
      ),
      mPowerUpList(powerUpList) {
    initPosition();
}

void Animal::onPlayerCollision(Player& player) {
    mPowerUpList.addPowerUp(getPowerUpType());
    getParent()->detachChild(*this);
}

void Animal::initPosition() {
    setPosition(sf::Vector2f(
        rand() % 16 * Global::TILE_SIZE, rand() % 9 * Global::TILE_SIZE
    ));
}

void Animal::updateCurrent(sf::Time deltaTime) { mAnimation.update(deltaTime); }

PowerUp::Type Animal::getPowerUpType() const { return PowerUp::Type::None; }
