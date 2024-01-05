#ifndef VEHICLE_LANE_HPP
#define VEHICLE_LANE_HPP

#include "../../Vehicle/Vehicle.hpp"
#include "../Lane.hpp"
#include "TrafficLight/TrafficLight.hpp"

class VehicleLane : public Lane {
   public:
    VehicleLane(TextureHolder& textureHolder, const sf::Vector2f& position);

    void handlePlayerCollision(Player& player) override;

   private:
    Textures::ID mTextureID;
    Directions::ID mDirection;
    sf::Vector2f mVelocity;
    std::deque<Vehicle*> mVehicles;
    int mTileToNextSpawns;
    TrafficLight* mTrafficLight;
    float mVelocityPercent;

    void buildScene();

    void init();

    void setVelocityPercent(float percent);

    Vehicle* createVehicle();
    void addVehicle();
    void removeVehicle();

    void updateCurrent(sf::Time deltaTime) override;
};

#endif
