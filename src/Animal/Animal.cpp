#include "Animal.hpp"

#include "../Global/Global.hpp"

Animal::Animal(
    TextureHolder& TextureHolder, Textures::ID textureID, sf::View& worldView,
    PowerUpList& powerUpList
)
    : SpriteNode(TextureHolder, textureID),
      mWorldView(worldView),
      mPowerUpList(powerUpList) {
    initPosition(worldView.getCenter());
}

void Animal::onPlayerCollision(Player& player) {
    mPowerUpList.addPowerUp(getPowerUpType());
    getParent()->detachChild(*this);
}

void Animal::initPosition(const sf::Vector2f& worldViewPosition) {
    sf::Vector2f position = worldViewPosition;
    int num = rand() % 16 - 8;
    position.x += num * Global::TILE_SIZE;
    num = rand() % 9 - 4;
    position.y += (num - .5f) * Global::TILE_SIZE;
    setPosition(position);
}
