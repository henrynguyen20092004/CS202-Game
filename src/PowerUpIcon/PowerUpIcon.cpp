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
    mTextNode = textnode.get();
    attachChild(std::move(textnode));
}

void PowerUpIcon::updateCurrent(sf::Time deltaTime) {
    float opacity = mCount ? 1.f : .5f;
    setOpacity(opacity);
    mTextNode->setOpacity(opacity);

    sf::Vector2f viewPosition =
        mWorldView.getCenter() - mWorldView.getSize() / 2.f;
    setPosition(viewPosition + mPositionOffset + sf::Vector2f(20.f, 20.f));

    mTextNode->setText("x" + std::to_string(mCount));
    mTextNode->setPosition(getSize() + sf::Vector2f(-10.f, -10.f));
}
