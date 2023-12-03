#ifndef VEHICLE_FACTORY_HPP
#define VEHICLE_FACTORY_HPP

#include <queue>

#include "../../Vehicle/Vehicle.hpp"
#include "../Factory.hpp"

class VehicleFactory : public Factory {
   public:
    VehicleFactory(TextureHolder& textureHolder);

   private:
    Directions::ID mDirection;
    Textures::ID mTextureID;
    sf::Vector2f mVelocity;
    sf::Time mSpawnTime;
    sf::Clock mSpawnClock;
    std::deque<Vehicle*> mVehicles;

    void addVehicle();
    void removeVehicle();

    void updateCurrent(sf::Time deltaTime) override;
};

#endif
