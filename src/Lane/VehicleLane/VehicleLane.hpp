#ifndef VEHICLE_LANE_HPP
#define VEHICLE_LANE_HPP

#include "../../Vehicle/Vehicle.hpp"
#include "../Lane.hpp"
#include "TrafficLight/TrafficLight.hpp"

class VehicleLane : public Lane {
   public:
    VehicleLane(
        TextureHolder& textureHolder, const sf::Vector2f& position,
        bool isLoading
    );

    void handlePlayerCollision(Player& player) override;

   private:
    Textures::ID mTextureID;
    Directions::ID mDirection = Directions::ID::None;
    sf::Vector2f mVelocity;
    std::deque<Vehicle*> mVehicles;
    int mTileToNextSpawns;
    TrafficLight* mTrafficLight;
    float mVelocityPercent;

    void buildScene(bool isLoading);

    void init();

    void setVelocityPercent(float percent);

    Vehicle* createVehicle();
    void addVehicle();
    void removeVehicle();

    Textures::ID getTextureID() const final;

    void updateCurrent(sf::Time deltaTime) override;

    void saveCurrent(std::ofstream& fout) const final;
    void loadCurrent(std::ifstream& fin) final;
};

#endif
