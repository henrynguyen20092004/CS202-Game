#ifndef VEHICLE_FACTORY_HPP
#define VEHICLE_FACTORY_HPP

#include <queue>

#include "../../Vehicle/Vehicle.hpp"
#include "../Factory.hpp"

class VehicleFactory : public Factory {
   public:
    typedef std::unique_ptr<VehicleFactory> Ptr;

    VehicleFactory(TextureHolder& textureHolder);

    Directions::ID getDirection() const;

    void setVelocityPercent(float percent);

    void handlePlayerCollision(Player& player) override;

   private:
    Textures::ID mTextureID;
    Directions::ID mDirection;
    sf::Vector2f mVelocity;
    sf::Time mSpawnClock;
    std::deque<Vehicle*> mVehicles;
    float mVelocityPercent;

    Vehicle* createVehicle();
    void init() override;

    void addVehicle();
    void removeVehicle();

    void updateCurrent(sf::Time deltaTime) override;
};

#endif
