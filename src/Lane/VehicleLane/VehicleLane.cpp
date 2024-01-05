#include "VehicleLane.hpp"

#include "../../Global/Global.hpp"
#include "../../Random/Random.hpp"
#include "../../Vehicle/Car/Car.hpp"

VehicleLane::VehicleLane(
    TextureHolder& textureHolder, const sf::Vector2f& position
)
    : Lane(textureHolder, position) {
    mDirection = Random<Directions::ID>::generate(
        {Directions::ID::Left, Directions::ID::Right}
    );

    mTextureID = Random<Textures::ID>::generate({Textures::ID::Car});

    mVelocity = sf::Vector2f(Random<float>::generate(100.f, 400.f), 0.f);

    buildScene();
    init();
}

void VehicleLane::handlePlayerCollision(Player& player) {
    for (auto vehicle : mVehicles) {
        vehicle->handlePlayerCollision(player);
    }
}

void VehicleLane::buildScene() {
    Lane::buildScene(Textures::ID::VehicleLane);

    for (int i = 0; i < Global::NUM_TILES_X; ++i) {
        SpriteNode::Ptr sprite(new SpriteNode(
            mTextureHolder, Textures::ID::VehicleLane,
            sf::IntRect(
                Random<int>::generate({0}) * Global::TILE_SIZE, 0,
                Global::TILE_SIZE, Global::TILE_SIZE
            )
        ));
        sprite->setPosition(i * Global::TILE_SIZE, 0.f);
        mSceneLayers[LaneLayer]->attachChild(std::move(sprite));
    }

    TrafficLight::Ptr trafficLight(new TrafficLight(mTextureHolder, mDirection)
    );
    mTrafficLight = trafficLight.get();
    mSceneLayers[SignalLightLayer]->attachChild(std::move(trafficLight));
}

void VehicleLane::init() {
    Vehicle::Ptr vehicle(createVehicle());
    vehicle->setVelocity(mVelocity);
    vehicle->setPosition(
        mDirection == Directions::ID::Left ? -vehicle->getSize().x
                                           : Global::WINDOW_WIDTH,
        (Global::TILE_SIZE - vehicle->getSize().y) / 2.f
    );
    mVehicles.push_front(vehicle.get());
    mSceneLayers[ObjectLayer]->attachChild(std::move(vehicle));
    mTileToNextSpawns = Random<int>::generate(
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, {5, 5, 5, 5, 10, 10, 10, 10, 20, 20}
    );
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
    vehicle->setPosition(sf::Vector2f(
        mDirection == Directions::ID::Left
            ? mVehicles.front()->getPosition().x +
                  mVehicles.front()->getSize().x +
                  mTileToNextSpawns * Global::TILE_SIZE
            : mVehicles.front()->getPosition().x -
                  mTileToNextSpawns * Global::TILE_SIZE - vehicle->getSize().x,
        (Global::TILE_SIZE - vehicle->getSize().y) / 2.f
    ));
    mVehicles.push_front(vehicle.get());
    mSceneLayers[ObjectLayer]->attachChild(std::move(vehicle));
    mTileToNextSpawns = Random<int>::generate(
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, {5, 5, 5, 5, 10, 10, 10, 10, 20, 20}
    );
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

    while ((mDirection == Directions::ID::Left &&
            mVehicles.front()->getPosition().x +
                    mVehicles.front()->getSize().x <
                Global::WINDOW_WIDTH - mTileToNextSpawns * Global::TILE_SIZE) ||
           (mDirection == Directions::ID::Right &&
            mVehicles.front()->getPosition().x >
                mTileToNextSpawns * Global::TILE_SIZE)) {
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
