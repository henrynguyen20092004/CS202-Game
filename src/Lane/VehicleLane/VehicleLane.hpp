#ifndef VEHICLE_LANE_HPP
#define VEHICLE_LANE_HPP

#include "../../Factory/VehicleFactory/VehicleFactory.hpp"
#include "../../TrafficLight/TrafficLight.hpp"
#include "../Lane.hpp"

class VehicleLane : public Lane {
   public:
    VehicleLane(TextureHolder& textureHolder, const sf::Vector2f& position);

    void handlePlayerCollision(Player& player) override;

   private:
    VehicleFactory* mVehicleFactory;
    TrafficLight* mTrafficLight;

    void buildScene();

    void updateCurrent(sf::Time deltaTime) override;
};

#endif
