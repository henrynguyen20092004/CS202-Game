#include "VehicleLane.hpp"

#include "../../Factory/VehicleFactory/VehicleFactory.hpp"
#include "../../TrafficLight/TrafficLight.hpp"

VehicleLane::VehicleLane(
    TextureHolder& textureHolder, const sf::Vector2f& position
)
    : Lane(textureHolder, position) {
    buildScene();
}

void VehicleLane::buildScene() {
    Lane::buildScene(Textures::ID::VehicleLane);
    VehicleFactory::Ptr factory(new VehicleFactory(mTextureHolder));
    mVehicleFactory = factory.get();
    mSceneLayers[ObjectLayer]->attachChild(std::move(factory));

    TrafficLight::Ptr trafficLight(
        new TrafficLight(mTextureHolder, mVehicleFactory->getDirection())
    );
    mTrafficLight = trafficLight.get();
    mSceneLayers[TrafficLightLayer]->attachChild(std::move(trafficLight));
}

void VehicleLane::updateCurrent(sf::Time deltaTime) {
    switch (mTrafficLight->getState()) {
        case TrafficLight::State::Green:
            mVehicleFactory->setVelocityPercent(1.f);
            break;

        case TrafficLight::State::Red:
            mVehicleFactory->setVelocityPercent(0.f);
            break;

        case TrafficLight::State::Yellow:
            mVehicleFactory->setVelocityPercent(0.5f);
            break;

        default:
            break;
    }
}
