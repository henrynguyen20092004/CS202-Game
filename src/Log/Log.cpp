#include "Log.hpp"

Log::Log(
    TextureHolder& textureHolder, Textures::ID textureID,
    sf::IntRect textureRect, Directions::ID direction
)
    : MovableSpriteNode(textureHolder, textureID, textureRect),
      mDirection(direction) {}

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
