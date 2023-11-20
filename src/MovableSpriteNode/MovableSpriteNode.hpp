#ifndef MOVABLE_SPRITE_NODE_HPP
#define MOVABLE_SPRITE_NODE_HPP

#include "../SpriteNode/SpriteNode.hpp"

class MovableSpriteNode : public SpriteNode {
   public:
    sf::Vector2f getVelocity() const;
    void setVelocity(sf::Vector2f velocity);
    void accelerate(sf::Vector2f velocity);

   private:
    sf::Vector2f mVelocity;

    virtual void updateCurrent(sf::Time deltaTime);
};

#endif
