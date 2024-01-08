#include "Player.hpp"

#include <cmath>

#include "../Blood/Blood.hpp"
#include "../Global/Global.hpp"
#include "../Score/Score.hpp"
#include "../TextNode/TextNode.hpp"

Player::Player(
    TextureHolder& textureHolder, Textures::ID textureID, sf::View& worldView,
    PlayerSettings& playerSettings, int playerNumber
)
    : Entity(textureHolder, textureID, sf::IntRect(0, 0, 60, 60)),
      mWorldView(worldView),
      mPlayerSettings(playerSettings),
      mPlayerNumber(playerNumber) {
    setHitbox(sf::FloatRect(10, 10, 40, 40));  // TODO: set hitbox properly
    setVelocity(sf::Vector2f(500.f, 500.f));

    Halo::Ptr halo(new Halo(mTextureHolder, Textures::ID::Halo));
    mHalo = halo.get();
    attachChild(std::move(halo));

    Blood::Ptr blood(new Blood(*this));
    attachChild(std::move(blood));
}

bool Player::askToMove() {
    if (mNeedToMove) {
        mNeedToMove = false;
        return true;
    }

    return false;
}

int Player::getPlayerNumber() const { return mPlayerNumber; }

void Player::setName(FontHolder& fontHolder) {
    TextNode::Ptr name(new TextNode(
        fontHolder, Fonts::ID::VTV323, "P" + std::to_string(mPlayerNumber + 1),
        30
    ));
    name->setPosition((getSize().x - name->getTextSize()) / 2.f, 70.f);
    attachChild(std::move(name));
}

Directions::ID Player::getDirection() const { return mDirection; }

Tile* Player::getSourceTile() const { return mSourceTile; }

Tile* Player::getTargetTile() const { return mTargetTile; }

void Player::setTargetTile(Tile* targetTile) {
    mTargetTile = targetTile;
    mIsMoving = true;
}

int Player::getMaxHealth() const { return mMaxHealth; }

int Player::getHealth() const { return mHealth; }

void Player::addRevival() {
    mHasRevival = true;
    mHalo->show();
}

void Player::addHealth() { mHealth = std::min(mHealth + 10, mMaxHealth); }

void Player::kill() { mHealth = 0; }

void Player::damage() { --mHealth; }

void Player::goBack() {
    if (!mIsMoving || mForceGoGack) {
        return;
    }

    std::swap(mSourceTile, mTargetTile);
    mForceGoGack = true;
}

bool Player::isImmortal() const { return mIsImmortal; }

void Player::setImortal(bool isImmortal) {
    mIsImmortal = isImmortal;

    if (mIsImmortal) {
        mImmortalTime = sf::seconds(100.f);
        setOpacity(0.5f);
    } else {
        setOpacity(1.f);
    }
}

bool Player::isAlive() {
    if (!isOutOfBounds() && mHealth > 0) {
        return true;
    }

    if (mHasRevival) {
        mHasRevival = false;
        setImortal(true);
        mImmortalTime = sf::seconds(2.f);
        mHealth = mMaxHealth;
        mHalo->hide();

        return true;
    }

    setTextureRect(sf::IntRect(240, 0, 60, 60));

    return false;
}

void Player::handlePlayerCollision(Player& player) {
    if (&player != this && collidePlayer(player) && !mIsImmortal) {
        goBack();
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
                mTargetTile->getVelocity().x * Global::SPEED_MODIFIER;
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

    if (mIsImmortal) {
        mImmortalTime -= deltaTime * Global::DIFFICULTY_MODIFIER;
        if (mImmortalTime <= sf::Time::Zero) {
            setImortal(false);
        }
    }
}

void Player::saveCurrent(std::ofstream& fout) const {
    Entity::saveCurrent(fout);
    fout << mIsImmortal << ' ';
    fout << mImmortalTime << '\n';
    fout << static_cast<int>(mDirection) << ' ' << mHalo->isShown() << ' '
         << mHealth << '\n';
    fout << mNeedToMove << ' ' << mIsMoving << ' ' << mForceGoGack << ' '
         << mHasRevival << '\n';
}

void Player::loadCurrent(std::ifstream& fin) {
    Entity::loadCurrent(fin);
    fin >> mIsImmortal;
    fin >> mImmortalTime;

    int direction;
    fin >> direction;
    mDirection = static_cast<Directions::ID>(direction);

    bool isHaloShown;
    fin >> isHaloShown >> mHealth;

    if (isHaloShown) {
        mHalo->show();
    } else {
        mHalo->hide();
    }

    fin >> mNeedToMove >> mIsMoving >> mForceGoGack >> mHasRevival;
}
