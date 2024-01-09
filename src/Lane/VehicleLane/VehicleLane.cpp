#include "VehicleLane.hpp"

#include "../../FileIO/FileIO.hpp"
#include "../../Global/Global.hpp"
#include "../../Random/Random.hpp"
#include "../../Vehicle/Bus/Bus.hpp"
#include "../../Vehicle/Car/Car.hpp"
#include "../../Vehicle/PoliceCar/PoliceCar.hpp"
#include "../../Vehicle/Van/Van.hpp"

VehicleLane::VehicleLane(
    TextureHolder& textureHolder, int seasonIndex, const sf::Vector2f& position,
    bool isLoading
)
    : Lane(textureHolder, seasonIndex, position) {
    buildScene(isLoading);

    if (isLoading) {
        return;
    }

    mTextureID = Random<Textures::ID>::generate(
        {Textures::ID::Car, Textures::ID::PoliceCar, Textures::ID::Van,
         Textures::ID::Bus},
        {30, 10, 30, 30}
    );
    mDirection = Random<Directions::ID>::generate(
        {Directions::ID::Left, Directions::ID::Right}
    );

    if (mTextureID == Textures::ID::PoliceCar) {
        mVelocity = sf::Vector2f(Random<float>::generate(600.f, 900.f), 0.f);
    } else {
        mVelocity = sf::Vector2f(Random<float>::generate(100.f, 400.f), 0.f);
    }

    init();
}

void VehicleLane::handlePlayerCollision(Player& player) {
    for (auto vehicle : mVehicles) {
        vehicle->handlePlayerCollision(player);
    }
}

void VehicleLane::buildScene(bool isLoading) {
    Lane::buildScene(Textures::ID::VehicleLane, isLoading);

    for (int i = 0; i < Global::NUM_TILES_X; ++i) {
        SpriteNode::Ptr sprite(new SpriteNode(
            mTextureHolder, Textures::ID::VehicleLane,
            sf::IntRect(
                Random<int>::generate({0}) * Global::TILE_SIZE,
                mSeasonIndex * Global::TILE_SIZE, Global::TILE_SIZE,
                Global::TILE_SIZE
            )
        ));
        sprite->setPosition(i * Global::TILE_SIZE, 0.f);
        mSceneLayers[LaneLayer]->attachChild(std::move(sprite));
    }

    TrafficLight::Ptr trafficLight(
        new TrafficLight(mTextureHolder, mSeasonIndex, mDirection, isLoading)
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
    if (mTextureID == Textures::ID::PoliceCar) {
        return;
    }

    mVelocityPercent = percent;

    for (auto vehicle : mVehicles) {
        vehicle->setVelocity(mVelocity * percent);
    }
}

Vehicle* VehicleLane::createVehicle() {
    switch (mTextureID) {
        case Textures::ID::Car:
            return new Car(mTextureHolder, mSeasonIndex, mDirection);

        case Textures::ID::PoliceCar:
            return new PoliceCar(mTextureHolder, mSeasonIndex, mDirection);

        case Textures::ID::Van:
            return new Van(mTextureHolder, mSeasonIndex, mDirection);

        case Textures::ID::Bus:
            return new Bus(mTextureHolder, mSeasonIndex, mDirection);

        default:
            return nullptr;
    }
}

void VehicleLane::addVehicle() {
    float frontVehiclePosX = mVehicles.front()->getPosition().x;
    Vehicle::Ptr vehicle(createVehicle());
    vehicle->setVelocity(mVelocity);
    vehicle->setPosition(
        mDirection == Directions::ID::Left
            ? frontVehiclePosX + mVehicles.front()->getSize().x +
                  mTileToNextSpawns * Global::TILE_SIZE
            : frontVehiclePosX - mTileToNextSpawns * Global::TILE_SIZE -
                  vehicle->getSize().x,
        (Global::TILE_SIZE - vehicle->getSize().y) / 2.f
    );
    mVehicles.push_front(vehicle.get());
    mSceneLayers[ObjectLayer]->attachChild(std::move(vehicle));

    if (mTextureID == Textures::ID::PoliceCar) {
        mTileToNextSpawns = Random<int>::generate({1, 15}, {80, 20});
    } else {
        mTileToNextSpawns = Random<int>::generate(
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
            {5, 5, 5, 5, 10, 10, 10, 10, 20, 20}
        );
    }
}

void VehicleLane::removeVehicle() {
    mSceneLayers[ObjectLayer]->detachChild(*mVehicles.back());
    mVehicles.pop_back();
}

Textures::ID VehicleLane::getTextureID() const {
    return Textures::ID::VehicleLane;
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

    while (mDirection == Directions::ID::Left &&
               mVehicles.front()->getPosition().x +
                       mVehicles.front()->getSize().x <
                   Global::WINDOW_WIDTH -
                       mTileToNextSpawns * Global::TILE_SIZE ||
           mDirection == Directions::ID::Right &&
               mVehicles.front()->getPosition().x >
                   mTileToNextSpawns * Global::TILE_SIZE) {
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

void VehicleLane::saveCurrent(std::ofstream& fout) const {
    Lane::saveCurrent(fout);
    int numVehicles = mVehicles.size();

    fout << static_cast<int>(mTextureID) << ' ' << static_cast<int>(mDirection)
         << '\n';
    fout << numVehicles << '\n';
    fout << mVelocity << '\n';
    fout << mVelocityPercent << ' ' << mTileToNextSpawns << '\n';
}

void VehicleLane::loadCurrent(std::ifstream& fin) {
    Lane::loadCurrent(fin);
    int textureID, direction, numVehicles;
    fin >> textureID >> direction >> numVehicles;
    mTextureID = static_cast<Textures::ID>(textureID);
    mDirection = static_cast<Directions::ID>(direction);

    for (int i = 0; i < numVehicles; ++i) {
        Vehicle::Ptr vehicle(createVehicle());
        mVehicles.push_front(vehicle.get());
        mSceneLayers[ObjectLayer]->attachChild(std::move(vehicle));
    }

    fin >> mVelocity >> mVelocityPercent >> mTileToNextSpawns;
    setVelocityPercent(mVelocityPercent);
}
