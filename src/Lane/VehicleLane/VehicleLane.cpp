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
    mVehicleFactory = factory.get();

    TrafficLight::Ptr trafficLight(
        new TrafficLight(mTextureHolder, factory->getDirection())
    );
    mTrafficLight = trafficLight.get();

    mSceneLayers[ObjectLayer]->attachChild(std::move(factory));
    mSceneLayers[TrafficLightLayer]->attachChild(std::move(trafficLight));
}

void VehicleLane::updateCurrent(sf::Time deltaTime) {
    switch (mTrafficLight->getState()) {
        case TrafficLightStates::ID::Green:
            mVehicleFactory->setVelocityPercent(1.f);
            break;

        case TrafficLightStates::ID::Red:
            mVehicleFactory->setVelocityPercent(0.f);
            break;

        case TrafficLightStates::ID::Yellow:
            mVehicleFactory->setVelocityPercent(0.5f);
            break;

        default:
            break;
    }
}
