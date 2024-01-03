#include "Entity.hpp"

#include "../Global/Global.hpp"
#include "../Player/Player.hpp"

sf::FloatRect Entity::getLocalHitbox() const { return mHitbox; }

sf::FloatRect Entity::getGlobalHitbox() const {
    return getWorldTransform().transformRect(mHitbox);
}

void Entity::setHitbox(const sf::FloatRect& hitbox) { mHitbox = hitbox; }

bool Entity::collidePlayer(const Player& player) const {
    return getGlobalHitbox().intersects(player.getGlobalHitbox());
}

void Entity::handlePlayerCollision(Player& player) {}

void Entity::updateCurrent(sf::Time deltaTime) {
    MovableSpriteNode::updateCurrent(deltaTime);
}

void Entity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    SpriteNode::drawCurrent(target, states);
    // drawHitbox(target, states);
}

void Entity::drawHitbox(sf::RenderTarget& target, sf::RenderStates states)
    const {
    sf::RectangleShape hitbox(sf::Vector2f(mHitbox.width, mHitbox.height));
    hitbox.setPosition(mHitbox.left, mHitbox.top);
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(1.f);

    target.draw(hitbox, states);
}
