#ifndef OBSTACLE_LANE_HPP
#define OBSTACLE_LANE_HPP

#include "../../Obstacle/Obstacle.hpp"
#include "../Lane.hpp"

class ObstacleLane : public Lane {
   public:
    ObstacleLane(
        TextureHolder& textureHolder, const sf::Vector2f& position,
        bool isEmpty = false
    );

    void handlePlayerCollision(Player& player) override;

   private:
    std::vector<Obstacle*> mObstacles;

    void buildScene(bool isEmpty);

    Obstacle* createObstacle(Textures::ID textureID);
    void init();
};

#endif
