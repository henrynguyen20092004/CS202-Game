#include "Lane.hpp"

Lane::Lane(TextureHolder& textureHolder, const sf::Vector2f& position)
    : mTextureHolder(textureHolder) {
    setPosition(position);
}

void Lane::updateCurrent(sf::Time deltaTime) { mFactory->update(deltaTime); }

void Lane::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    target.draw(mSceneGraph, states);
}
