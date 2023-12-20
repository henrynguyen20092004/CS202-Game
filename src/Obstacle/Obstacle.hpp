#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "../SpriteNode/SpriteNode.hpp"

class Obstacle : public SpriteNode {
   public:
    typedef std::unique_ptr<Obstacle> Ptr;

    using SpriteNode::SpriteNode;

   private:
    void onPlayerCollision(Player& player) override;
};

#endif
