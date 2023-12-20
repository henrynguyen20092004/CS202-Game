#include "SpriteNode.hpp"

SpriteNode::SpriteNode(
    TextureHolder& textureHolder, Textures::ID textureID,
    sf::IntRect textureRect
)
    : mTextureHolder(textureHolder) {
    setSprite(textureID, textureRect);
}

void SpriteNode::setSprite(Textures::ID textureID, sf::IntRect textureRect) {
    mSprite.setTexture(mTextureHolder.get(textureID));

    if (textureRect != sf::IntRect()) {
        mSprite.setTextureRect(textureRect);
    }
}

sf::Vector2f SpriteNode::getSize() const {
    return mSprite.getLocalBounds().getSize();
}

sf::FloatRect SpriteNode::getLocalBounds() const {
    return mSprite.getLocalBounds();
}

sf::FloatRect SpriteNode::getGlobalBounds() const {
    return getWorldTransform().transformRect(getLocalBounds());
}

void SpriteNode::onPlayerCollision(Player& player) {}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(mSprite, states);
}

void SpriteNode::drawBoundingRect(
    sf::RenderTarget& target, sf::RenderStates states
) const {
    sf::RectangleShape shape(getSize());
    shape.setPosition(getPosition());
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Green);
    shape.setOutlineThickness(2.f);

    target.draw(shape, states);
}
