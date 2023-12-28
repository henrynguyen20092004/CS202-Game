#ifndef TRAIN_FACTORY_HPP
#define TRAIN_FACTORY_HPP

#include "../../Vehicle/Vehicle.hpp"
#include "../Factory.hpp"

class TrainFactory : public Factory {
   public:
    typedef std::unique_ptr<TrainFactory> Ptr;

    TrainFactory(TextureHolder& textureHolder);

    void handlePlayerCollision(Player& player) override;

   private:
    Directions::ID mDirection;
    sf::Vector2f mVelocity;
    sf::Time mSpawnClock;
    Vehicle* mTrain;

    void addTrain();
    void removeTrain();

    void updateCurrent(sf::Time deltaTime) override;
};

#endif
