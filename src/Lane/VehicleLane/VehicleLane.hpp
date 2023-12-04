#ifndef VEHICLE_LANE_HPP
#define VEHICLE_LANE_HPP

#include "../../Factory/VehicleFactory/VehicleFactory.hpp"
#include "../Lane.hpp"

class VehicleLane : public Lane {
   public:
    VehicleLane(TextureHolder& textureHolder, const sf::Vector2f& position);

   private:
    void buildScene();
};

#endif
