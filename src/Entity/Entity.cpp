#include "Entity.hpp"

#include "../Player/Player.hpp"

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
}

void Entity::saveCurrent(std::ofstream& fout) const {
    MovableSpriteNode::saveCurrent(fout);
    fout << mHitbox << '\n';
}

void Entity::loadCurrent(std::ifstream& fin) {
    MovableSpriteNode::loadCurrent(fin);
    fin >> mHitbox;
}
