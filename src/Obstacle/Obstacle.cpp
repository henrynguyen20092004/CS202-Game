#include "Obstacle.hpp"
Obstacle::Obstacle(float mX, float mY, float mWidth, float mHeight): mX(mX), mY(mY), mWidth(mWidth), mHeight(mHeight) {}
Obstacle::~Obstacle() {}
void Obstacle::draw(sf::RenderWindow& window) const {
    sf::RectangleShape rectangle(sf::Vector2f(mWidth, mHeight));
    rectangle.setPosition(mX, mY);
    rectangle.setFillColor(sf::Color::Red);
    window.draw(rectangle);
}