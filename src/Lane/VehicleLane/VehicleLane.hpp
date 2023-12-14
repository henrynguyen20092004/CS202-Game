#ifndef VEHICLE_LANE_HPP
#define VEHICLE_LANE_HPP

#include "../Lane.hpp"

class VehicleLane : public Lane {
   public:
    VehicleLane(TextureHolder& textureHolder, const sf::Vector2f& position);
    Factory* mVehicleFactory;
    TrafficLight* mTrafficLight;

   private:
    void buildScene();
};

#endif
