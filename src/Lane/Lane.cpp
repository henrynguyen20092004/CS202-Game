#include "Lane.hpp"

Lane::Lane(TextureHolder& textureHolder, const sf::Vector2f& position)
    : mTextureHolder(textureHolder), mFactory(nullptr) {
    setPosition(position);
}

void Lane::buildScene(Textures::ID textureID) {
    for (int i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();
        attachChild(std::move(layer));
    }

    SpriteNode::Ptr sprite(new SpriteNode(mTextureHolder, textureID));
    mSceneLayers[Ground]->attachChild(std::move(sprite));
}