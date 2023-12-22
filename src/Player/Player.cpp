#include "Player.hpp"

#include <cmath>

#include "../Global/Global.hpp"

Player::Player(
    TextureHolder& textureHolder, sf::View& worldView,
    PlayerSettings& playerSettings
)
    : MovableSpriteNode(textureHolder, Textures::ID::Player),
      mWorldView(worldView),
      mPlayerSettings(playerSettings),
      mDirection(Directions::ID::None),
      mIsMoving(false) {
    initPosition(worldView.getCenter());
    initTargetDistance();
    setVelocity(sf::Vector2f(500.f, 500.f));
}

void Player::damage() { --mHealth; }

void Player::heal() { ++mHealth; }

void Player::remainPosition() {
    mDirection = static_cast<Directions::ID>(static_cast<int>(mDirection) ^ 1);
    mTargetPosition += mTargetDistance[mDirection];
}

bool Player::isAlive() const { return !isOutOfBounds() && mHealth > 0; }

void Player::initPosition(const sf::Vector2f& viewCenter) {
    sf::Vector2f spawnOffset(
        (Global::TILE_SIZE - getLocalBounds().width) / 2.f,
        Global::TILE_SIZE * 2.5f
    );
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

void Player::handleEventCurrent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        Directions::ID direction = mPlayerSettings.getDirection(event.key.code);

        if (!mIsMoving && direction != Directions::ID::None) {
            mDirection = direction;
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

        float displacement =
            ((static_cast<int>(mDirection) < 2) ? mVelocity.x : mVelocity.y) *
            deltaTime.asSeconds();
        if (distance <= displacement) {
            setPosition(mTargetPosition);
            mIsMoving = false;
        } else {
            movement *= displacement / distance;
            move(movement);
        }
    }
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
