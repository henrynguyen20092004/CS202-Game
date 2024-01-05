#include "Blood.hpp"

Blood::Blood(TextureHolder& textureHolder, int& Health)
    : SpriteNode(textureHolder, Textures::ID::Blood), mHealth(Health) {}

void Blood::updateCurrent(sf::Time deltaTime) {
    if (mHealth == 0) {
        mSprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
    } else if (mHealth == 1) {
        mSprite.setTextureRect(sf::IntRect(0, 0, 30, 8));
    } else if (mHealth == 2) {
        mSprite.setTextureRect(sf::IntRect(0, 0, 60, 8));
    } else if (mHealth == 3) {
        mSprite.setTextureRect(sf::IntRect(0, 0, 90, 8));
    }
}