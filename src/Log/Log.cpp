#include "Log.hpp"

Log::Log(
    TextureHolder& textureHolder, Textures::ID textureID,
    Directions::ID direction
)
    : MovableSpriteNode(textureHolder, textureID), mDirection(direction) {}

Directions::ID Log::getDirection() const { return mDirection; }

void Log::setDirection(Directions::ID direction) { mDirection = direction; }

void Log::updateCurrent(sf::Time deltaTime) {
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
