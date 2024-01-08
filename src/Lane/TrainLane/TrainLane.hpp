#ifndef TRAIN_LANE_HPP
#define TRAIN_LANE_HPP

#include "../../Vehicle/Vehicle.hpp"
#include "../Lane.hpp"
#include "RailwaySignal/RailwaySignal.hpp"

class TrainLane : public Lane {
   public:
    TrainLane(TextureHolder& textureHolder, const sf::Vector2f& position, bool isLoading);

    void handlePlayerCollision(Player& player) override;

   private:
    Directions::ID mDirection;
    sf::Vector2f mVelocity;
    sf::Time mSpawnClock;
    Vehicle* mTrain = nullptr;
    RailwaySignal* mRailwaySignal;

    void buildScene(bool isLoading);

    void addTrain();
    void removeTrain();

    Textures::ID getTextureID() const final;

    void updateCurrent(sf::Time deltaTime) override;

    void saveCurrent(std::ofstream& fout) const final;
    void loadCurrent(std::ifstream& fin) final;
};

#endif
