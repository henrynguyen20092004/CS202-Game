#include "VehicleLane.hpp"

#include "../../Factory/VehicleFactory/VehicleFactory.hpp"
#include "../../Obstacle/TrafficLight/TrafficLight.hpp"

VehicleLane::VehicleLane(
    TextureHolder& textureHolder, const sf::Vector2f& position
)
    : Lane(textureHolder, position) {
    buildScene();
}

void VehicleLane::buildScene() {
    Lane::buildScene(Textures::ID::VehicleLane);
    Factory::Ptr factory(new VehicleFactory(mTextureHolder));

    SpriteNode::Ptr trafficLightSprite(
        new TrafficLight(mTextureHolder, factory->getDirection())
    );

    mSceneLayers[ObjectLayer]->attachChild(std::move(factory));
    mSceneLayers[TrafficLightLayer]->attachChild(std::move(trafficLightSprite));
}
