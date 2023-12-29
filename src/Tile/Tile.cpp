#include "Tile.hpp"

#include <cmath>

#include "../Global/Global.hpp"

Tile::Tile(Type type, sf::Vector2f position) : mType(type) {
    setPosition(position);
}

Tile::Type Tile::getType() const { return mType; }

float Tile::distanceTo(const Tile& other) const {
    return std::sqrt(
        std::pow(getPosition().x - other.getPosition().x, 2) +
        std::pow(getPosition().y - other.getPosition().y, 2)
    );
}

void Tile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    sf::RectangleShape rect(sf::Vector2f(Global::TILE_SIZE, Global::TILE_SIZE));
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(
        mType == Type::Good ? sf::Color::Green : sf::Color::Red
    );
    rect.setOutlineThickness(1.f);

    target.draw(rect, states);
}
