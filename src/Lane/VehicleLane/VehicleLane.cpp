#include "VehicleLane.hpp"

VehicleLane::VehicleLane(
    TextureHolder& textureHolder, const sf::Vector2f& position
)
    : Lane(textureHolder, position) {
    buildScene();
}

void VehicleLane::buildScene() {
    Lane::buildScene(Textures::ID::VehicleLane);
    Factory::Ptr factory(new VehicleFactory(mTextureHolder));
    mFactory = factory.get();
    mSceneLayers[ObjectLayer]->attachChild(std::move(factory));
}
