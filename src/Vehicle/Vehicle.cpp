#include "Vehicle.hpp"

Vehicle::Vehicle(Directions::ID direction, float speed)
    : mDirection(direction), mSpeed(speed) {}

Directions::ID Vehicle::getDirection() const { return mDirection; }

float Vehicle::getSpeed() const { return mSpeed; }

void Vehicle::setDirection(Directions::ID direction) { mDirection = direction; }

void Vehicle::setSpeed(float speed) { mSpeed = speed; }

void Vehicle::update(float deltaTime) {
    sf::Vector2f movement(0.f, 0.f);

    switch (mDirection) {
        case Directions::ID::Left:
            movement.x -= mSpeed;
            break;

        case Directions::ID::Right:
            movement.x += mSpeed;
            break;

        default:
            break;
    }

    move(movement * deltaTime);
}

void Vehicle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mSprite, states);
}
