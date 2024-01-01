#include "SpriteNode.hpp"

SpriteNode::SpriteNode(
    TextureHolder& textureHolder, Textures::ID textureID,
    sf::IntRect textureRect
)
    : mTextureHolder(textureHolder) {
    setSprite(textureID, textureRect);
}

void SpriteNode::centerOrigin() {
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
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

void SpriteNode::flipHorizontally() {
    sf::IntRect textureRect = mSprite.getTextureRect();
    textureRect.left += textureRect.width;
    textureRect.width = -textureRect.width;
    mSprite.setTextureRect(textureRect);
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(mSprite, states);
}
