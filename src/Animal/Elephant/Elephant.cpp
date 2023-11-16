#include"Elephant.hpp"

Elephant::Elephant(const sf::Vector2f& position ,TextureHolder& textureHolder)
    : Animal(position) {
    mSprite.setTexture(textureHolder.get(Textures::ID::Elephant));
}

Elephant::~Elephant() {}

void Elephant::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mSprite, states);
}

//void Elephant::update(float dt) {
    // mPosition.x += mSpeed * dt;
    // if (mPosition.x > 800) {
    //     mPosition.x = -100;
    // }
    // setDirection(1);
    // setSpeed(100);
    // mPosition.x += getSpeed() * dt;
    // if (mPosition.x > 800) {
    //     mPosition.x = -100;
    // }
    // setDirection(1);
    // setSpeed(100);
    // mPosition.x += getSpeed() * dt;
    // if (mPosition.x > 800) {
    //     mPosition.x = -100;
    // }
    // setDirection(1);
    // setSpeed(100);
    // mPosition.x += getSpeed() * dt;
    // if (mPosition.x > 800) {
    //     mPosition.x = -100;
    // }
    // setDirection(1);
    // setSpeed(100);
    // mPosition.x += getSpeed() * dt;
    // if (mPosition.x > 800) {
    //     mPosition.x = -100;
    // }
    // setDirection(1);
    // setSpeed(100);
    // mPosition.x += getSpeed() * dt;
    // if (mPosition.x > 800) {
    //     mPosition.x = -100;
    // }
    // setDirection(1);
    // setSpeed(100);
    // mPosition.x += getSpeed() * dt;
    // if (mPosition.x > 800) {
    //     mPosition.x = -100
