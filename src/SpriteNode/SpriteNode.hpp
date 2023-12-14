#ifndef SPRITE_NODE_HPP
#define SPRITE_NODE_HPP

#include "../ResourceHolder/ResourceHolder.hpp"
#include "../SceneNode/SceneNode.hpp"

class SpriteNode : public SceneNode {
   public:
    SpriteNode(
        TextureHolder& textureHolder, Textures::ID textureID,
        sf::IntRect textureRect = sf::IntRect()
    );

    void setSprite(
        Textures::ID textureID, sf::IntRect textureRect = sf::IntRect()
    );
    //void setScale(sf::Vector2f scale);
    sf::Vector2f getSize() const;
    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const override;

    virtual void onPlayerCollision(Player& player);

   protected:
    TextureHolder& mTextureHolder;

   private:
    sf::Sprite mSprite;

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const override;
    void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states)
        const;
};

#endif
