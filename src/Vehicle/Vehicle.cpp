#include "Vehicle.hpp"

void Vehicle::setPosition(const sf::Vector2f& position) {
    mPosition = position;
}

sf::Vector2f Vehicle::getPosition() const { return mPosition; }

void Vehicle::setDirection(int direction) { mDirection = direction; }

int Vehicle::getDirection() const { return mDirection; }

void Vehicle::setSpeed(float speed) { mSpeed = speed; }

float Vehicle::getSpeed() const { return mSpeed; }

Vehicle::Vehicle(const sf::Vector2f& position, int direction, float speed)
    : mPosition(position), mDirection(direction), mSpeed(speed) {}

Vehicle::~Vehicle() {}

void Vehicle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
}
