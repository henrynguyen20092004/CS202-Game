#include "Lane.hpp"

#include "../Obstacle/TrafficLight/TrafficLight.hpp"

Lane::Lane(TextureHolder& textureHolder, const sf::Vector2f& position)
    : mTextureHolder(textureHolder) {
    setPosition(position);
}

void Lane::buildScene(Textures::ID textureID) {
    for (int i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();
        attachChild(std::move(layer));
    }

    SpriteNode::Ptr sprite(new SpriteNode(mTextureHolder, textureID));

    mSceneLayers[LaneLayer]->attachChild(std::move(sprite));
}
