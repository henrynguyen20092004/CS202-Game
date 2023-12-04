#include "Player.hpp"

#include <stdexcept>

#include "../Global/Global.hpp"

struct PlayerMover {
    PlayerMover(float vx, float vy) : velocity(vx, vy) {}
    void operator()(Player& player) const { player.move(velocity); }

    sf::Vector2f velocity;
};

Player::Player(TextureHolder& textureHolder, sf::View& worldView)
    : SpriteNode(textureHolder, Textures::ID::Player), mWorldView(worldView) {
    initializePosition(worldView.getCenter());
    initializeKeyBinding();
    initializeActionBinding();
}

void Player::updateCurrent(sf::Time deltaTime) {
    if (isOutOfBounds()) {
        die();
    }
}

void Player::assignKey(sf::Keyboard::Key key, Action action) {
    auto found = mKeyBinding.find(key);

    if (found != mKeyBinding.end()) {
        mKeyBinding.erase(found);
    }

    mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const {
    for (auto pair : mKeyBinding) {
        if (pair.second == action) {
            return pair.first;
        }
    }

    return sf::Keyboard::Unknown;
}

void Player::handleEventCurrent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        auto found = mKeyBinding.find(event.key.code);

        if (found != mKeyBinding.end()) {
            mActionBinding[found->second](*this);
        }
    }
}

void Player::initializePosition(const sf::Vector2f& viewCenter) {
    centerOrigin();
    sf::Vector2f spawnOffset(Global::TILE_SIZE / 2.f, Global::TILE_SIZE * 3.f);
    setPosition(viewCenter + spawnOffset);
}

void Player::initializeKeyBinding() {
    mKeyBinding[sf::Keyboard::Up] = Action::MoveUp;
    mKeyBinding[sf::Keyboard::Left] = Action::MoveLeft;
    mKeyBinding[sf::Keyboard::Down] = Action::MoveDown;
    mKeyBinding[sf::Keyboard::Right] = Action::MoveRight;

    mKeyBinding[sf::Keyboard::W] = Action::MoveUp;
    mKeyBinding[sf::Keyboard::A] = Action::MoveLeft;
    mKeyBinding[sf::Keyboard::S] = Action::MoveDown;
    mKeyBinding[sf::Keyboard::D] = Action::MoveRight;
}

void Player::initializeActionBinding() {
    mActionBinding[Action::MoveUp] = PlayerMover(0.f, -Global::TILE_SIZE);
    mActionBinding[Action::MoveLeft] = PlayerMover(-Global::TILE_SIZE, 0.f);
    mActionBinding[Action::MoveDown] = PlayerMover(0.f, Global::TILE_SIZE);
    mActionBinding[Action::MoveRight] = PlayerMover(Global::TILE_SIZE, 0.f);
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
