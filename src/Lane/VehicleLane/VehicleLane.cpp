#include "VehicleLane.hpp"

VehicleLane::VehicleLane(
    TextureHolder& textureHolder, const sf::Vector2f& position
)
    : Lane(textureHolder, position) {
    buildScene();
}

void VehicleLane::buildScene() {
    for (int i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }

    Factory::Ptr factory(new VehicleFactory(mTextureHolder));
    mFactory = factory.get();
    mSceneLayers[Object]->attachChild(std::move(factory));

    SpriteNode::Ptr sprite(
        new SpriteNode(mTextureHolder, Textures::ID::VehicleLane)
    );
    mSceneLayers[Ground]->attachChild(std::move(sprite));
}
