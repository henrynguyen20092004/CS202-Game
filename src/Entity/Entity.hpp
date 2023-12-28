#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../SpriteNode/SpriteNode.hpp"

class Player;

class Entity : public SpriteNode {
   public:
    typedef std::unique_ptr<Entity> Ptr;

    using SpriteNode::SpriteNode;

    sf::FloatRect getLocalHitbox() const;
    sf::FloatRect getGlobalHitbox() const;
    sf::Vector2f getVelocity() const;

    void setHitbox(const sf::FloatRect& hitbox);
    void setVelocity(const sf::Vector2f& velocity);

    void accelerate(const sf::Vector2f& velocity);

    bool collidePlayer(const Player& player) const;
    virtual void handlePlayerCollision(Player& player);

   protected:
    virtual void updateCurrent(sf::Time deltaTime) override;

    void drawHitbox(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const override;

   private:
    sf::FloatRect mHitbox;
    sf::Vector2f mVelocity;
};

#endif
