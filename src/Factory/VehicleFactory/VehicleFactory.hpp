#ifndef VEHICLE_FACTORY_HPP
#define VEHICLE_FACTORY_HPP

#include <queue>

#include "../../Vehicle/Vehicle.hpp"
#include "../Factory.hpp"

class VehicleFactory : public Factory {
   public:
    VehicleFactory(TextureHolder& textureHolder);

    Directions::ID getDirection() const;

   private:
    Textures::ID mTextureID;
    Directions::ID mDirection;
    sf::Vector2f mVelocity;
    sf::Time mSpawnClock;
    std::deque<Vehicle*> mVehicles;

    void addVehicle();
    void removeVehicle();

    void setVelocityPercent(float percent) override;

    void updateCurrent(sf::Time deltaTime) override;
};

#endif
