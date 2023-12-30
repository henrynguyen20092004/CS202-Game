#ifndef VEHICLE_LANE_HPP
#define VEHICLE_LANE_HPP

#include "../../TrafficLight/TrafficLight.hpp"
#include "../../Vehicle/Vehicle.hpp"
#include "../Lane.hpp"

class VehicleLane : public Lane {
   public:
    VehicleLane(TextureHolder& textureHolder, const sf::Vector2f& position);

    void handlePlayerCollision(Player& player) override;

   private:
    Textures::ID mTextureID;
    Directions::ID mDirection;
    sf::Vector2f mVelocity;
    sf::Time mSpawnClock;
    std::deque<Vehicle*> mVehicles;
    float mVelocityPercent;
    TrafficLight* mTrafficLight;

    void buildScene();

    void setVelocityPercent(float percent);
    Vehicle* createVehicle();
    void init();
    void addVehicle();
    void removeVehicle();

    void updateCurrent(sf::Time deltaTime) override;
};

#endif
