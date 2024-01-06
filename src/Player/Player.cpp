#include "Player.hpp"

#include <cmath>

#include "../Global/Global.hpp"
#include "../Score/Score.hpp"

Player::Player(
    TextureHolder& textureHolder, Textures::ID textureID, sf::View& worldView,
    PlayerSettings& playerSettings
)
    : Entity(textureHolder, textureID, sf::IntRect(0, 0, 60, 60)),
      mWorldView(worldView),
      mPlayerSettings(playerSettings) {
    setHitbox(sf::FloatRect(10, 10, 40, 40));  // TODO: set hitbox properly
    setVelocity(sf::Vector2f(500.f, 500.f));
    Blood::Ptr blood(new Blood(textureHolder, mHealth));
    mBlood = blood.get();
    attachChild(std::move(blood));

    mBlood->setPosition(10.f, -10.f);
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

bool Player::getImmortal() const { return mIsImmortal; }

void Player::setTargetTile(Tile* targetTile) {
    mTargetTile = targetTile;
    mIsMoving = true;
}

void Player::setImmortal(bool isImmortal) { mIsImmortal = isImmortal; }

void Player::kill() { mHealth = 0; }

void Player::damage() { --mHealth; }

void Player::heal() {if(mHealth<=90) mHealth+=10; }

void Player::goBack() {
    if (!mIsMoving || mForceGoGack) {
        return;
    }

    std::swap(mSourceTile, mTargetTile);
    mForceGoGack = true;
}

void Player::setScorePtr(Score* score) { mScore = score; }

void Player::addBonusScore() const { mScore->addBonus(); }

bool Player::isAlive() const { return !isOutOfBounds() && mHealth > 0; }

void Player::handlePlayerCollision(Player& player) {
    if (&player != this && collidePlayer(player) && !mIsImmortal) {
        goBack();
    }
}

void Player::handleEventCurrent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        Directions::ID direction = mPlayerSettings.getDirection(event.key.code);

        if (!mIsMoving && direction != Directions::ID::None) {
            mDirection = direction;
            mNeedToMove = true;
            setTextureRect(
                sf::IntRect(static_cast<int>(mDirection) * 60, 0, 60, 60)
            );
        }
    }
}

void Player::updateCurrent(sf::Time deltaTime) {
    sf::Vector2f positionInTile =
        (sf::Vector2f(Global::TILE_SIZE, Global::TILE_SIZE) - getSize()) / 2.f;

    if (mIsMoving) {
        sf::Vector2f targetPosition =
            mTargetTile->getWorldPosition() + positionInTile;
        sf::Vector2f movement = targetPosition - getWorldPosition();
        float distance = std::hypotf(movement.x, movement.y),
              velocity = getVelocity().x;

        if (!movement.y) {
            velocity +=
                (movement.x < 0 ? -1 : 1) *
                (mTargetTile->getDirection() == Directions::ID::Left ? -1 : 1) *
                mTargetTile->getVelocity().x;
        }

        float displacement =
            velocity * Global::DIFFICULTY_MODIFIER * deltaTime.asSeconds();

        if (distance <= displacement) {
            setPosition(targetPosition);
            mDirection = Directions::ID::None;
            mSourceTile = mTargetTile;
            mTargetTile = nullptr;
            mIsMoving = false;
            mForceGoGack = false;
        } else {
            movement *= displacement / distance;
            move(movement);
        }
    } else {
        if (mSourceTile->getType() == Tile::Type::Bad && !mIsImmortal) {
            damage();
        }

        setPosition(mSourceTile->getWorldPosition() + positionInTile);
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
