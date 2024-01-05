#include "Tile.hpp"

#include <cmath>

#include "../Global/Global.hpp"

Tile::Tile(Type type, sf::Vector2f position, Directions::ID direction)
    : mType(type), mDirection(direction) {
    setPosition(position);
}

Tile::Type Tile::getType() const { return mType; }

Directions::ID Tile::getDirection() const { return mDirection; }

sf::Vector2f Tile::getVelocity() const { return mVelocity; }

void Tile::setDirection(Directions::ID direction) { mDirection = direction; }

void Tile::setVelocity(const sf::Vector2f& velocity) { mVelocity = velocity; }

float Tile::distanceTo(Tile* other) const {
    sf::Vector2f position = getWorldPosition(),
                 otherPosition = other->getWorldPosition();

    return std::hypotf(
        position.x - otherPosition.x, position.y - otherPosition.y
    );
}

void Tile::updateCurrent(sf::Time deltaTime) {
    switch (mDirection) {
        case Directions::ID::Left:
            move(
                -mVelocity * Global::SPEED_MODIFIER *
                Global::DIFFICULTY_MODIFIER * deltaTime.asSeconds()
            );
            break;

        case Directions::ID::Right:
            move(
                mVelocity * Global::SPEED_MODIFIER *
                Global::DIFFICULTY_MODIFIER * deltaTime.asSeconds()
            );
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
