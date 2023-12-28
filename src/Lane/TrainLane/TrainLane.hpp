#ifndef TRAIN_LANE_HPP
#define TRAIN_LANE_HPP

#include "../../Factory/TrainFactory/TrainFactory.hpp"
#include "../Lane.hpp"

class TrainLane : public Lane {
   public:
    TrainLane(TextureHolder& textureHolder, const sf::Vector2f& position);

    void handlePlayerCollision(Player& player) override;

   private:
    TrainFactory* mTrainFactory;

    void buildScene();
};

#endif
