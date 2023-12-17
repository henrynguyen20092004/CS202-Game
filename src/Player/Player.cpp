#include "Player.hpp"

#include <cmath>
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
    initPosition(worldView.getCenter());
    initTargetDistance();
}

void Player::damage() { --mHealth; }

void Player::heal() { ++mHealth; }

bool Player::isAlive() const {
    if (isOutOfBounds() || mHealth <= 0) {
        return false;
    }
    return true;
}

void Player::handleEventCurrent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        Directions::ID direction = mPlayerSettings.getDirection(event.key.code);

        if (!mIsMoving && direction != Directions::ID::None) {
            mTargetPosition = getPosition() + mTargetDistance[direction];
            mIsMoving = true;
        }
    }
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
}

void Player::initPosition(const sf::Vector2f& viewCenter) {
    sf::Vector2f spawnOffset(0, Global::TILE_SIZE * 2.5f);
    setPosition(viewCenter + spawnOffset);
}

void Player::initTargetDistance() {
    mTargetDistance[Directions::ID::Up] = sf::Vector2f(0.f, -Global::TILE_SIZE);
    mTargetDistance[Directions::ID::Down] =
        sf::Vector2f(0.f, Global::TILE_SIZE);
    mTargetDistance[Directions::ID::Left] =
        sf::Vector2f(-Global::TILE_SIZE, 0.f);
    mTargetDistance[Directions::ID::Right] =
        sf::Vector2f(Global::TILE_SIZE, 0.f);
}

bool Player::isOutOfBounds() const {
    sf::FloatRect hitbox = getGlobalBounds(),
                  viewBounds = sf::FloatRect(
                      mWorldView.getCenter().x - mWorldView.getSize().x / 2.f,
                      mWorldView.getCenter().y - mWorldView.getSize().y / 2.f,
                      mWorldView.getSize().x, mWorldView.getSize().y
                  );

    return !viewBounds.intersects(hitbox);
}

// // TODO: Customize
// void Player::dieOutofBounds() { throw std::runtime_error("Player died!"); }
