#ifndef SPRITE_NODE_HPP
#define SPRITE_NODE_HPP

#include "../Identifier/Identifier.hpp"
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

    sf::Vector2f getSize() const;
    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;

   protected:
    TextureHolder& mTextureHolder;

    void centerOrigin();

   private:
    sf::Sprite mSprite;

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const override;
};

#endif
