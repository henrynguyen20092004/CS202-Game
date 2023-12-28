#ifndef OBSTACLE_FACTORY_HPP
#define OBSTACLE_FACTORY_HPP

#include "../../Obstacle/Obstacle.hpp"
#include "../Factory.hpp"

class ObstacleFactory : public Factory {
   public:
    typedef std::unique_ptr<ObstacleFactory> Ptr;

    ObstacleFactory(TextureHolder& textureHolder, bool isEmpty = false);

    void handlePlayerCollision(Player& player) override;

   private:
    std::vector<Obstacle*> mObstacles;

    Obstacle* createObstacle(Textures::ID textureID);

    void init() override;
};

#endif
