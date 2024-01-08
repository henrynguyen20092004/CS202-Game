#include "PowerUpIcon.hpp"

#include "../Global/Global.hpp"

PowerUpIconArgs::PowerUpIconArgs(
    TextureHolder& textureHolder, FontHolder& fontHolder, sf::View& worldView,
    sf::Vector2f positionOffset
)
    : textureHolder(textureHolder),
      fontHolder(fontHolder),
      worldView(worldView),
      positionOffset(positionOffset) {}

PowerUpIcon::PowerUpIcon(
    const PowerUpIconArgs& powerUpIconArgs, Textures::ID textureID, int& count
)
    : SpriteNode(powerUpIconArgs.textureHolder, textureID),
      mWorldView(powerUpIconArgs.worldView),
      mPositionOffset(powerUpIconArgs.positionOffset),
      mCount(count) {
    TextNode::Ptr textnode(new TextNode(
        powerUpIconArgs.fontHolder, Fonts::ID::VTV323,
        "x" + std::to_string(mCount), 30
    ));
    setTextureRect(sf::IntRect(0, 0, 90, 90));

    mTextNode = textnode.get();
    attachChild(std::move(textnode));
}

void PowerUpIcon::updateCurrent(sf::Time deltaTime) {
    sf::Vector2f viewPosition =
        mWorldView.getCenter() - mWorldView.getSize() / 2.f;

    setPosition(viewPosition + mPositionOffset);
    mTextNode->setText("x" + std::to_string(mCount));
    mTextNode->setPosition(90.f, 75.f);
}
