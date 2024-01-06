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
    void updateCurrent(sf::Time deltaTime) override;

    void drawHitbox(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const override;

    void saveCurrent(std::ofstream& fout) const override;
    void loadCurrent(std::ifstream& fin) override;

   private:
    sf::FloatRect mHitbox;
};

#endif
