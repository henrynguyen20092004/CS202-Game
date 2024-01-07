#include "Vehicle.hpp"

#include "../Player/Player.hpp"

Vehicle::Vehicle(
    TextureHolder& textureHolder, Textures::ID textureID,
    Directions::ID direction
)
    : Entity(textureHolder, textureID), mDirection(direction) {}

Directions::ID Vehicle::getDirection() const { return mDirection; }

void Vehicle::setDirection(Directions::ID direction) { mDirection = direction; }

void Vehicle::handlePlayerCollision(Player& player) {
    if (!player.isImmortal() && collidePlayer(player)) {
        player.damage();
    }
}

void Vehicle::updateCurrent(sf::Time deltaTime) {
    switch (mDirection) {
        case Directions::ID::Left:
            Entity::updateCurrent(-deltaTime);
            break;

        case Directions::ID::Right:
            Entity::updateCurrent(deltaTime);
            break;

        default:
            break;
    }
}
