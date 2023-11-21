#ifndef SPRITE_NODE_HPP
#define SPRITE_NODE_HPP

#include "../SceneNode/SceneNode.hpp"

class SpriteNode : public SceneNode {
   public:
    SpriteNode(
        const sf::Texture& texture,
        const sf::IntRect& textureRect = sf::IntRect()
    );

   private:
    sf::Sprite mSprite;

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const;
};

#endif
