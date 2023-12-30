#include "Tile.hpp"

#include <cmath>

#include "../Global/Global.hpp"

Tile::Tile(Type type, sf::Vector2f position)
    : mType(type), mDirection(Directions::ID::None) {
    setPosition(position);
}

Tile::Type Tile::getType() const { return mType; }

Directions::ID Tile::getDirection() const { return mDirection; }

sf::Vector2f Tile::getVelocity() const { return mVelocity; }

void Tile::setDirection(Directions::ID direction) { mDirection = direction; }

void Tile::setVelocity(sf::Vector2f velocity) { mVelocity = velocity; }

float Tile::distanceTo(Tile* tile) const {
    sf::Vector2f thisPosition = getPosition();
    sf::Vector2f tilePosition = tile->getPosition();

    return std::hypotf(
        thisPosition.x - tilePosition.x, thisPosition.y - tilePosition.y
    );
}

void Tile::updateCurrent(sf::Time deltaTime) {
    switch (mDirection) {
        case Directions::ID::Left:
            move(-mVelocity * Global::SPEED_MODIFIER * deltaTime.asSeconds());
            break;

        case Directions::ID::Right:
            move(mVelocity * Global::SPEED_MODIFIER * deltaTime.asSeconds());
            break;

        default:
            break;
    }
}

void Tile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    // sf::RectangleShape rect(sf::Vector2f(Global::TILE_SIZE,
    // Global::TILE_SIZE)); rect.setFillColor(sf::Color::Transparent);
    // rect.setOutlineColor(
    //     mType == Type::Good ? sf::Color::Green : sf::Color::Red
    // );
    // rect.setOutlineThickness(1.f);

    // target.draw(rect, states);
}
