#include "Obstacle.hpp"
Obstacle::Obstacle(float mX, float mY, float mWidth, float mHeight)
    : mX(mX), mY(mY), mWidth(mWidth), mHeight(mHeight) {}
Obstacle::~Obstacle() {}
void Obstacle::draw(sf::RenderWindow& window) const {
    sf::RectangleShape rectangle(sf::Vector2f(mWidth, mHeight));
    rectangle.setPosition(mX, mY);
    rectangle.setFillColor(sf::Color::Red);
    window.draw(rectangle);
}
bool Obstacle::isColliding(const sf::FloatRect& other) const {
        return sf::FloatRect(mX, mY, mWidth, mHeight).intersects(other);
}
float Obstacle::getX() const { return mX; }
float Obstacle::getY() const { return mY; }
float Obstacle::getWidth() const { return mWidth; }
float Obstacle::getHeight() const { return mHeight; }
void Obstacle::setX(float mX) { this->mX = mX; }
void Obstacle::setY(float mY) { this->mY = mY; }
void Obstacle::setWidth(float mWidth) { this->mWidth = mWidth; }
void Obstacle::setHeight(float mHeight) { this->mHeight = mHeight; }