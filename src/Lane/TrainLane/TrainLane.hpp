#ifndef TRAIN_LANE_HPP
#define TRAIN_LANE_HPP

#include "../../Vehicle/Vehicle.hpp"
#include "../Lane.hpp"
#include "RailwaySignal/RailwaySignal.hpp"

class TrainLane : public Lane {
   public:
    TrainLane(TextureHolder& textureHolder, const sf::Vector2f& position);

    void handlePlayerCollision(Player& player) override;

   private:
    Directions::ID mDirection;
    sf::Vector2f mVelocity;
    sf::Time mSpawnClock;
    Vehicle* mTrain;
    RailwaySignal* mRailwaySignal;

    void buildScene();

    void addTrain();
    void removeTrain();

    void updateCurrent(sf::Time deltaTime) override;
};

#endif
