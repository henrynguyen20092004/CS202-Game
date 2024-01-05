#include "RailwaySignal.hpp"

#include "../../../Global/Global.hpp"

RailwaySignal::RailwaySignal(TextureHolder& textureHolder)
    : SpriteNode(textureHolder, Textures::ID::RailwaySignal) {
    sf::Vector2u textureSize =
        mTextureHolder.get(Textures::ID::RailwaySignal).getSize();

    setTextureRect(sf::IntRect(
        textureSize.x * RailwaySignal::State::Green / 2, 0, textureSize.x / 2,
        textureSize.y
    ));

    setPosition(Global::WINDOW_WIDTH / 2 - getSize().x / 2, 0);
}

#include <iostream>

void RailwaySignal::switchState(RailwaySignal::State state) {
    sf::Vector2u textureSize =
        mTextureHolder.get(Textures::ID::RailwaySignal).getSize();

    setTextureRect(sf::IntRect(
        textureSize.x * state / 2, 0, textureSize.x / 2, textureSize.y
    ));
}
