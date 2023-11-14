#include "Obstacle.hpp"
Obstacle::Obstacle(
    sf::Vector2f position, float width, float height,
    const std::string& texturePath
)
    : mPosition(position), mWidth(width), mHeight(height) {
    // Load texture
    sf::Texture texture;
    if (!texture.loadFromFile(texturePath)) {
        throw std::runtime_error("LoadFromFile failed");
    }
}
Obstacle::~Obstacle() {}
void Obstacle::draw(sf::RenderWindow& window) const {
    sf::RectangleShape obstacle(sf::Vector2f(mWidth, mHeight));
    obstacle.setPosition(mPosition);
    obstacle.setFillColor(sf::Color::Red);
    window.draw(obstacle);
}
bool Obstacle::isColliding(const sf::FloatRect& other) const {
    sf::FloatRect obstacle(mPosition, sf::Vector2f(mWidth, mHeight));
    return obstacle.intersects(other);
}
float Obstacle::getX() const { return mPosition.x; }
float Obstacle::getY() const { return mPosition.y; }
float Obstacle::getWidth() const { return mWidth; }
float Obstacle::getHeight() const { return mHeight; }
void Obstacle::setX(float mX) { mPosition.x = mX; }
void Obstacle::setY(float mY) { mPosition.y = mY; }
void Obstacle::setWidth(float mWidth) { this->mWidth = mWidth; }
void Obstacle::setHeight(float mHeight) { this->mHeight = mHeight; }