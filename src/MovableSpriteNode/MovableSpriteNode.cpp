#include "MovableSpriteNode.hpp"

MovableSpriteNode::MovableSpriteNode(
    TextureHolder& textureHolder, Textures::ID textureID,
    sf::IntRect textureRect
)
    : SpriteNode(textureHolder, textureID, textureRect) {}

sf::Vector2f MovableSpriteNode::getVelocity() const { return mVelocity; }

void MovableSpriteNode::setVelocity(const sf::Vector2f& velocity) {
    mVelocity = velocity;
}

void MovableSpriteNode::accelerate(const sf::Vector2f& velocity) {
    mVelocity += velocity;
}

void MovableSpriteNode::updateCurrent(sf::Time deltaTime) {
    move(mVelocity * deltaTime.asSeconds());
}
