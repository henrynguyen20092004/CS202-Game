#include "VehicleFactory.hpp"

#include "../../Global/Global.hpp"
#include "../../Random/Random.hpp"

VehicleFactory::VehicleFactory(TextureHolder& textureHolder)
    : Factory(textureHolder) {
    mDirection = Random<Directions::ID>::generate(
        {Directions::ID::Left, Directions::ID::Right}
    );

    mTextureID = Random<Textures::ID>::generate({Textures::ID::Car});

    mVelocity = sf::Vector2f(Random<float>::generate(100.f, 500.f), 0.f);
}

void VehicleFactory::addVehicle() {
    Vehicle::Ptr vehicle(new Vehicle(mTextureHolder, mTextureID, mDirection));
    vehicle->setVelocity(mVelocity);
    if (mDirection == Directions::ID::Left) {
        vehicle->setPosition(
            Global::WINDOW_WIDTH + vehicle->getSize().x,
            (Global::TILE_SIZE - vehicle->getSize().y) / 2.f
        );
    } else {
        vehicle->setPosition(
            -vehicle->getSize().x,
            (Global::TILE_SIZE - vehicle->getSize().y) / 2.f
        );
    }

    mVehicles.push_front(vehicle.get());
    attachChild(std::move(vehicle));
}

void VehicleFactory::removeVehicle() {
    Vehicle* vehicle = mVehicles.back();
    detachChild(*vehicle);
    mVehicles.pop_back();
}

void VehicleFactory::updateCurrent(sf::Time deltaTime) {
    if (mSpawnClock.getElapsedTime() > mSpawnTime) {
        addVehicle();

        mSpawnClock.restart();
        mSpawnTime = sf::Time(sf::seconds(Random<float>::generate(2.f, 5.f)));
    }

    if (!mVehicles.empty()) {
        Vehicle* vehicle = mVehicles.back();
        if (mDirection == Directions::ID::Left) {
            if (vehicle->getPosition().x < -vehicle->getSize().x) {
                removeVehicle();
            }
        } else {
            if (vehicle->getPosition().x >
                Global::WINDOW_WIDTH + vehicle->getSize().x) {
                removeVehicle();
            }
        }
    }
}
