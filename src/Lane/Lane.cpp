#include "Lane.hpp"

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

    SpriteNode::Ptr trafficLightSprite(
        new SpriteNode(mTextureHolder, Textures::ID::TrafficLight)
    );
    trafficLightSprite->setScale(0.25f, 0.15f);

    mSceneLayers[LaneLayer]->attachChild(std::move(sprite));
    mSceneLayers[ObjectLayer]->attachChild(std::move(trafficLightSprite));
}
