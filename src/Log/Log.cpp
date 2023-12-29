#include "Log.hpp"

Log::Log(
    TextureHolder& textureHolder, Textures::ID textureID,
    Directions::ID direction
)
    : Entity(textureHolder, textureID), mDirection(direction) {}

Directions::ID Log::getDirection() const { return mDirection; }

void Log::setDirection(Directions::ID direction) { mDirection = direction; }

void Log::handlePlayerCollision(Player& player) {
    if (collidePlayer(player)) {
        // TODO: Attach player to log
    }
}

void Log::updateCurrent(sf::Time deltaTime) {
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
