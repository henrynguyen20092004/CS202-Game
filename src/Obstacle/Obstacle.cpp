#include "Obstacle.hpp"

Obstacle::Obstacle() {}

Obstacle::Obstacle(const sf::Vector2f& size)
    : mSize(size) {}

sf::Vector2f Obstacle::getSize() const { return mSize; }

void Obstacle::setSize(const sf::Vector2f& size) { mSize = size; }

void Obstacle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
}

bool Obstacle::isColliding(const sf::FloatRect& otherHitBox) const {
    sf::FloatRect hitBox(getPosition(), mSize);
    return hitBox.intersects(otherHitBox);
}

Obstacle::~Obstacle() {}
