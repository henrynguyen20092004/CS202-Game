#include "Animal.hpp"

void Animal::setPosition(const sf::Vector2f& position) {
    mPosition = position;
}

sf::Vector2f Animal::getPosition() const { return mPosition; }

// void Animal::setDirection(int direction) { mDirection = direction; }

// int Animal::getDirection() const { return mDirection; }

// void Animal::setSpeed(float speed) { mSpeed = speed; }

// float Animal::getSpeed() const { return mSpeed; }

Animal::Animal(const sf::Vector2f& position)
    : mPosition(position){}

Animal::~Animal() {}

void Animal::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
}