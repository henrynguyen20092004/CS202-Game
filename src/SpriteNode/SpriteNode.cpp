#include "SpriteNode.hpp"

SpriteNode::SpriteNode(
    const sf::Texture& texture, const sf::IntRect& textureRect
)
    : mSprite(texture, textureRect) {}

void SpriteNode::centerOrigin() {
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void SpriteNode::setTexture(
    const sf::Texture& texture, const sf::IntRect& textureRect
) {
    mSprite.setTexture(texture);
    mSprite.setTextureRect(textureRect);
}

sf::FloatRect SpriteNode::getHitbox() const {
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(mSprite, states);
}
