#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "../SpriteNode/SpriteNode.hpp"

class Obstacle : public SpriteNode {
   public:
    typedef std::unique_ptr<Obstacle> Ptr;

    Obstacle(TextureHolder& textureHolder, Textures::ID texureID);

   private:
    void onPlayerCollision(Player& player) override;
};

#endif
