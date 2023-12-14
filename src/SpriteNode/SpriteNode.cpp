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

// void SpriteNode::setScale(sf::Vector2f scale) {
//     mSprite.setScale(scale);
// }

sf::Vector2f SpriteNode::getSize() const {
    return sf::Vector2f(
        mSprite.getTextureRect().width, mSprite.getTextureRect().height
    );
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
    sf::FloatRect rect = getLocalBounds();

    sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));
    shape.setPosition(sf::Vector2f(rect.left, rect.top));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Green);
    shape.setOutlineThickness(2.f);

    target.draw(shape, states);
}
