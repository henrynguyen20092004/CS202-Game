#include "VehicleLane.hpp"

#include "../../Global/Global.hpp"
#include "../../Random/Random.hpp"
#include "../../Vehicle/Car/Car.hpp"

VehicleLane::VehicleLane(
    TextureHolder& textureHolder, const sf::Vector2f& position
)
    : Lane(textureHolder, position) {
    buildScene();

    mDirection = Random<Directions::ID>::generate(
        {Directions::ID::Left, Directions::ID::Right}
    );

    mTextureID = Random<Textures::ID>::generate({Textures::ID::Car});

    mVelocity = sf::Vector2f(Random<float>::generate(100.f, 500.f), 0.f);
    mSpawnClock = sf::seconds(Random<float>::generate(1.f, 5.f));

    init();
}

void VehicleLane::handlePlayerCollision(Player& player) {
    for (auto vehicle : mVehicles) {
        vehicle->handlePlayerCollision(player);
    }
}

void VehicleLane::buildScene() {
    Lane::buildScene(Textures::ID::VehicleLane);

    TrafficLight::Ptr trafficLight(new TrafficLight(mTextureHolder, mDirection)
    );
    mTrafficLight = trafficLight.get();
    mSceneLayers[TrafficLightLayer]->attachChild(std::move(trafficLight));
}

void VehicleLane::init() {
    float vehicleWidth = mTextureHolder.get(mTextureID).getSize().x;
    int numVehicles = std::min(
        Random<int>::generate(0, Global::WINDOW_WIDTH / vehicleWidth + 1), 3
    );
    std::vector<float> positions;

    for (int i = 0; i < numVehicles; ++i) {
        positions.push_back(Random<float>::generate(
            -vehicleWidth, Global::WINDOW_WIDTH - numVehicles * vehicleWidth
        ));
    }

    std::sort(positions.begin(), positions.end());

    for (int i = 0; i < numVehicles; ++i) {
        positions[i] += i * vehicleWidth;

        Vehicle::Ptr vehicle(createVehicle());
        vehicle->setVelocity(mVelocity);
        vehicle->setPosition(
            positions[i], (Global::TILE_SIZE - vehicle->getSize().y) / 2.f
        );

        mVehicles.push_front(vehicle.get());
        mSceneLayers[ObjectLayer]->attachChild(std::move(vehicle));
    }
}

void VehicleLane::setVelocityPercent(float percent) {
    mVelocityPercent = percent;

    for (auto vehicle : mVehicles) {
        vehicle->setVelocity(mVelocity * percent);
    }
}

Vehicle* VehicleLane::createVehicle() {
    switch (mTextureID) {
        case Textures::ID::Car:
            return new Car(mTextureHolder, mDirection);

        default:
            return nullptr;
    }
}

void VehicleLane::addVehicle() {
    Vehicle::Ptr vehicle(createVehicle());
    vehicle->setVelocity(mVelocity);
    vehicle->setPosition(
        mDirection == Directions::ID::Left ? Global::WINDOW_WIDTH
                                           : -vehicle->getSize().x,
        (Global::TILE_SIZE - vehicle->getSize().y) / 2.f
    );
    mVehicles.push_front(vehicle.get());
    mSceneLayers[ObjectLayer]->attachChild(std::move(vehicle));
    mSpawnClock = sf::seconds(Random<float>::generate(1.f, 5.f));
}

void VehicleLane::removeVehicle() {
    mSceneLayers[ObjectLayer]->detachChild(*mVehicles.back());
    mVehicles.pop_back();
}

void VehicleLane::updateCurrent(sf::Time deltaTime) {
    switch (mTrafficLight->getState()) {
        case TrafficLight::State::Green:
            setVelocityPercent(1.f);
            break;

        case TrafficLight::State::Red:
            setVelocityPercent(0.f);
            break;

        case TrafficLight::State::Yellow:
            setVelocityPercent(0.5f);
            break;

        default:
            break;
    }

    mSpawnClock -= deltaTime * Global::SPEED_MODIFIER * mVelocityPercent;

    if (mSpawnClock < sf::Time::Zero) {
        addVehicle();
    }

    if (!mVehicles.empty()) {
        Vehicle* vehicle = mVehicles.back();

        if (mDirection == Directions::ID::Left &&
                vehicle->getPosition().x < -vehicle->getSize().x ||
            mDirection == Directions::ID::Right &&
                vehicle->getPosition().x > Global::WINDOW_WIDTH) {
            removeVehicle();
        }
    }
}
