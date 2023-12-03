#ifndef MOVABLE_SPRITE_NODE_HPP
#define MOVABLE_SPRITE_NODE_HPP

#include "../SpriteNode/SpriteNode.hpp"

class MovableSpriteNode : public SpriteNode {
   public:
    MovableSpriteNode(
        TextureHolder& textureHolder, Textures::ID textureID,
        sf::IntRect textureRect = sf::IntRect()
    );

    sf::Vector2f getVelocity() const;
    void setVelocity(const sf::Vector2f& velocity);
    void accelerate(const sf::Vector2f& velocity);

   protected:
    virtual void updateCurrent(sf::Time deltaTime) override;

   private:
    sf::Vector2f mVelocity;
};

#endif
