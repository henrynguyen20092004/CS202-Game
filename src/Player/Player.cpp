#include "Player.hpp"

#include <math.h>

#include <stdexcept>

#include "../Global/Global.hpp"

Player::Player(
    TextureHolder& textureHolder, sf::View& worldView,
    PlayerSettings& playerSettings
)
    : SpriteNode(textureHolder, Textures::ID::Player),
      mWorldView(worldView),
      mPlayerSettings(playerSettings),
      mIsMoving(false) {
    initializeTargetDistance();
    initializePosition(worldView.getCenter());
}

void Player::updateCurrent(sf::Time deltaTime) {
    if (mIsMoving) {
        sf::Vector2f movement = mTargetPosition - getPosition();
        float distance =
            std::sqrt(movement.x * movement.x + movement.y * movement.y);

        if (distance <= mVelocity * deltaTime.asSeconds()) {
            setPosition(mTargetPosition);
            mIsMoving = false;
        } else {
            movement *= mVelocity * deltaTime.asSeconds() / distance;
            move(movement);
        }
    }

    if (isOutOfBounds()) {
        die();
    }
}

void Player::handleEventCurrent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (!mIsMoving && mPlayerSettings.getDirection(event.key.code) !=
                              Directions::ID::None) {
            mDirection = mPlayerSettings.getDirection(event.key.code);
            mTargetPosition = getPosition() + mTargetDistance[mDirection];
            mIsMoving = true;
        }
    }
}

void Player::initializeTargetDistance() {
    mTargetDistance[Directions::ID::Up] = sf::Vector2f(0.f, -Global::TILE_SIZE);
    mTargetDistance[Directions::ID::Down] =
        sf::Vector2f(0.f, Global::TILE_SIZE);
    mTargetDistance[Directions::ID::Left] =
        sf::Vector2f(-Global::TILE_SIZE, 0.f);
    mTargetDistance[Directions::ID::Right] =
        sf::Vector2f(Global::TILE_SIZE, 0.f);
}

void Player::initializePosition(const sf::Vector2f& viewCenter) {
    centerOrigin();
    sf::Vector2f spawnOffset(Global::TILE_SIZE / 2.f, Global::TILE_SIZE * 3.f);
    setPosition(viewCenter + spawnOffset);
}

bool Player::isOutOfBounds() {
    sf::FloatRect hitbox = getGlobalBounds(),
                  viewBounds = sf::FloatRect(
                      mWorldView.getCenter().x - mWorldView.getSize().x / 2.f,
                      mWorldView.getCenter().y - mWorldView.getSize().y / 2.f,
                      mWorldView.getSize().x, mWorldView.getSize().y
                  );

    return !viewBounds.intersects(hitbox);
}

// TODO: Customize
void Player::die() { throw std::runtime_error("Player died!"); }
