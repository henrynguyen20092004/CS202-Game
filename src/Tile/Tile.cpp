#include "Tile.hpp"

#include <cmath>

#include "../Global/Global.hpp"

Tile::Tile(Type type, sf::Vector2f position) : mType(type) {
    setPosition(position);
}

Tile::Type Tile::getType() const { return mType; }

float Tile::distanceTo(Tile* tile) const {
    sf::Vector2f thisPosition = getPosition();
    sf::Vector2f tilePosition = tile->getPosition();

    return std::sqrt(
        (thisPosition.x - tilePosition.x) * (thisPosition.x - tilePosition.x) +
        (thisPosition.y - tilePosition.y) * (thisPosition.y - tilePosition.y)
    );
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
