#include "MovableSpriteNode.hpp"

#include "../Global/Global.hpp"

sf::Vector2f MovableSpriteNode::getVelocity() const { return mVelocity; }

void MovableSpriteNode::setVelocity(const sf::Vector2f& velocity) {
    mVelocity = velocity;
}

void MovableSpriteNode::accelerate(const sf::Vector2f& velocity) {
    mVelocity += velocity;
}

void MovableSpriteNode::updateCurrent(sf::Time deltaTime) {
    move(mVelocity * Global::SPEED_MODIFIER * deltaTime.asSeconds());
}
