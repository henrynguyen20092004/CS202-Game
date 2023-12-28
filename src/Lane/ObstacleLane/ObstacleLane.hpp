#ifndef OBSTACLE_LANE_HPP
#define OBSTACLE_LANE_HPP

#include "../../Factory/ObstacleFactory/ObstacleFactory.hpp"
#include "../Lane.hpp"

class ObstacleLane : public Lane {
   public:
    ObstacleLane(
        TextureHolder& textureHolder, const sf::Vector2f& position,
        bool isEmpty = false
    );

    void handlePlayerCollision(Player& player) override;

   private:
    ObstacleFactory* mObstacleFactory;

    void buildScene(bool isEmpty);
};

#endif
