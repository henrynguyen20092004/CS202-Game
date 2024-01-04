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

   private:
    std::vector<Obstacle*> mObstacles;

    void handlePlayerCollision(Player& player) override;

    void buildScene(bool isEmpty);

    void init();

    Obstacle* createObstacle(Textures::ID textureID);
};

#endif
