#ifndef TRAIN_FACTORY_HPP
#define TRAIN_FACTORY_HPP

#include "../../Vehicle/Vehicle.hpp"
#include "../Factory.hpp"

class TrainFactory : public Factory {
   public:
    TrainFactory(TextureHolder& textureHolder);

   private:
    Textures::ID mTextureID;
    Directions::ID mDirection;
    sf::Vector2f mVelocity;
    sf::Time mSpawnTime;
    sf::Time mSpawnClock;
    Vehicle* mTrain;

    void addTrain();
    void removeTrain();

    void updateCurrent(sf::Time deltaTime) override;
};

#endif
