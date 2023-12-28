#include "VehicleFactory.hpp"

#include "../../Global/Global.hpp"
#include "../../Random/Random.hpp"
#include "../../Vehicle/Car/Car.hpp"

VehicleFactory::VehicleFactory(TextureHolder& textureHolder)
    : Factory(textureHolder), mVelocityPercent(1.f) {
    mDirection = Random<Directions::ID>::generate(
        {Directions::ID::Left, Directions::ID::Right}
    );

    mTextureID = Random<Textures::ID>::generate({Textures::ID::Car});

    mVelocity = sf::Vector2f(Random<float>::generate(100.f, 500.f), 0.f);
    mSpawnClock = sf::seconds(Random<float>::generate(1.f, 5.f));

    init();
}

Directions::ID VehicleFactory::getDirection() const { return mDirection; }

void VehicleFactory::setVelocityPercent(float percent) {
    mVelocityPercent = percent;

    for (auto vehicle : mVehicles) {
        vehicle->setVelocity(mVelocity * percent);
    }
}

void VehicleFactory::handlePlayerCollision(Player& player) {
    for (auto vehicle : mVehicles) {
        vehicle->handlePlayerCollision(player);
    }
}

Vehicle* VehicleFactory::createVehicle() {
    switch (mTextureID) {
        case Textures::ID::Car:
            return new Car(mTextureHolder, mDirection);

        default:
            return nullptr;
    }
}

void VehicleFactory::init() {
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
        attachChild(std::move(vehicle));
    }
}

void VehicleFactory::addVehicle() {
    Vehicle::Ptr vehicle(createVehicle());
    vehicle->setVelocity(mVelocity);
    vehicle->setPosition(
        mDirection == Directions::ID::Left ? Global::WINDOW_WIDTH
                                           : -vehicle->getSize().x,
        (Global::TILE_SIZE - vehicle->getSize().y) / 2.f
    );
    mVehicles.push_front(vehicle.get());
    attachChild(std::move(vehicle));
}

void VehicleFactory::removeVehicle() {
    detachChild(*mVehicles.back());
    mVehicles.pop_back();
}

void VehicleFactory::updateCurrent(sf::Time deltaTime) {
    mSpawnClock -= deltaTime * Global::SPEED_MODIFIER * mVelocityPercent;

    if (mSpawnClock < sf::Time::Zero) {
        addVehicle();
        mSpawnClock = sf::seconds(Random<float>::generate(1.f, 5.f));
    }

    if (!mVehicles.empty()) {
        Vehicle* vehicle = mVehicles.back();

        if (mDirection == Directions::ID::Left) {
            if (vehicle->getPosition().x < -vehicle->getSize().x) {
                removeVehicle();
            }
        } else {
            if (vehicle->getPosition().x > Global::WINDOW_WIDTH) {
                removeVehicle();
            }
        }
    }
}
