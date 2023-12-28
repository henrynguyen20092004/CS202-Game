#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "../Entity/Entity.hpp"

class Obstacle : public Entity {
   public:
    typedef std::unique_ptr<Obstacle> Ptr;

   protected:
    Obstacle(TextureHolder& textureHolder);

   public:
    void handlePlayerCollision(Player& player) override;
};

#endif
