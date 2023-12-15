#include "Vehicle.hpp"

Vehicle::Vehicle(
    TextureHolder& textureHolder, Textures::ID texureID,
    Directions::ID direction
)
    : MovableSpriteNode(textureHolder, texureID), mDirection(direction) {}

Directions::ID Vehicle::getDirection() const { return mDirection; }

void Vehicle::setDirection(Directions::ID direction) { mDirection = direction; }

void Vehicle::updateCurrent(sf::Time deltaTime) {
    switch (mDirection) {
        case Directions::ID::Left:
            MovableSpriteNode::updateCurrent(-deltaTime);
            break;

        case Directions::ID::Right:
            MovableSpriteNode::updateCurrent(deltaTime);
            break;

        default:
            break;
    }
}
