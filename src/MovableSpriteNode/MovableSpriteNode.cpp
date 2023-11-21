#include "MovableSpriteNode.hpp"

sf::Vector2f MovableSpriteNode::getVelocity() const { return mVelocity; }

void MovableSpriteNode::setVelocity(sf::Vector2f velocity) {
    mVelocity = velocity;
}

void MovableSpriteNode::accelerate(sf::Vector2f velocity) {
    mVelocity += velocity;
}

void MovableSpriteNode::updateCurrent(sf::Time deltaTime) {
    move(mVelocity * deltaTime.asSeconds());
}
