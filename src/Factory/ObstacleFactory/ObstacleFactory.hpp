#ifndef OBSTACLE_FACTORY_HPP
#define OBSTACLE_FACTORY_HPP

#include "../../Obstacle/Obstacle.hpp"
#include "../Factory.hpp"

class ObstacleFactory : public Factory {
   public:
    ObstacleFactory(TextureHolder& textureHolder, bool isEmpty = false);

   private:
    void init() override;
};

#endif
