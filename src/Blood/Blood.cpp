#include "Blood.hpp"

Blood::Blood(TextureHolder& textureHolder, int& Health)
    : SpriteNode(textureHolder, Textures::ID::Blood), mHealth(Health) {
        setPosition(0, 90);
    }

void Blood::updateCurrent(sf::Time deltaTime) {
    setTextureRect(sf::IntRect(0, 0, mHealth, 10));
}