#include "Player.hpp"

#include <cmath>

#include "../Global/Global.hpp"

Player::Player(
    TextureHolder& textureHolder, sf::View& worldView,
    PlayerSettings& playerSettings
)
    : Entity(textureHolder, Textures::ID::Player),
      mWorldView(worldView),
      mPlayerSettings(playerSettings),
      mDirection(Directions::ID::None),
      mIsMoving(false),
      mNeedToMove(false),
      mForceGoGack(false) {
    setHitbox(sf::FloatRect(10, 10, 60, 60));  // TODO: set hitbox properly
    setVelocity(sf::Vector2f(500.f, 500.f));
}

bool Player::askToMove() {
    if (mNeedToMove) {
        mNeedToMove = false;
        return true;
    }

    return false;
}

Directions::ID Player::getDirection() const { return mDirection; }

Tile* Player::getSourceTile() const { return mSourceTile; }

Tile* Player::getTargetTile() const { return mTargetTile; }

void Player::setTargetTile(Tile* targetTile) {
    mTargetTile = targetTile;
    mIsMoving = true;
}

void Player::kill() { mHealth = 0; }

void Player::damage() { --mHealth; }

void Player::heal() { ++mHealth; }

void Player::goBack() {
    if (mForceGoGack) {
        return;
    }

    std::swap(mSourceTile, mTargetTile);
    mForceGoGack = true;
}

bool Player::isAlive() const { return !isOutOfBounds() && mHealth > 0; }

void Player::handleEventCurrent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        Directions::ID direction = mPlayerSettings.getDirection(event.key.code);

        if (!mIsMoving && direction != Directions::ID::None) {
            mDirection = direction;
            mNeedToMove = true;
        }
    }
}

void Player::updateCurrent(sf::Time deltaTime) {
    if (mIsMoving) {
        sf::Vector2f targetPosition =
            mTargetTile->getGlobalPosition() +
            (sf::Vector2f(Global::TILE_SIZE, Global::TILE_SIZE) - getSize()) /
                2.f;
        sf::Vector2f movement = targetPosition - getGlobalPosition();
        float distance = std::hypotf(movement.x, movement.y);
        float velocity = getVelocity().x;
        if (mDirection == Directions::ID::Left ||
            mDirection == Directions::ID::Right) {
            velocity +=
                (mDirection == Directions::ID::Left ? -1 : 1) *
                (mTargetTile->getDirection() == Directions::ID::Left ? -1 : 1) *
                mTargetTile->getVelocity().x;
        }

        float displacement = velocity * deltaTime.asSeconds();

        if (distance <= displacement) {
            setPosition(targetPosition);
            mSourceTile = mTargetTile;
            mTargetTile = nullptr;
            mIsMoving = false;
            mForceGoGack = false;
        } else {
            movement *= displacement / distance;
            move(movement);
        }
    } else {
        if (mSourceTile->getType() == Tile::Type::Bad) {
            damage();
        }

        setPosition(
            mSourceTile->getGlobalPosition() +
            (sf::Vector2f(Global::TILE_SIZE, Global::TILE_SIZE) - getSize()) /
                2.f
        );
    }
}

bool Player::isOutOfBounds() const {
    sf::FloatRect viewBounds = sf::FloatRect(
        mWorldView.getCenter().x - mWorldView.getSize().x / 2.f,
        mWorldView.getCenter().y - mWorldView.getSize().y / 2.f,
        mWorldView.getSize().x, mWorldView.getSize().y
    );

    return !viewBounds.intersects(getGlobalBounds());
}
