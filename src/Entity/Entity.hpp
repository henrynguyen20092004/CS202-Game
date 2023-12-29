#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../MovableSpriteNode/MovableSpriteNode.hpp"

class Player;

class Entity : public MovableSpriteNode {
   public:
    typedef std::unique_ptr<Entity> Ptr;

    using MovableSpriteNode::MovableSpriteNode;

    sf::FloatRect getLocalHitbox() const;
    sf::FloatRect getGlobalHitbox() const;

    void setHitbox(const sf::FloatRect& hitbox);

    bool collidePlayer(const Player& player) const;
    virtual void handlePlayerCollision(Player& player);

   protected:
    virtual void updateCurrent(sf::Time deltaTime) override;

    void drawHitbox(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const override;

   private:
    sf::FloatRect mHitbox;
};

#endif
