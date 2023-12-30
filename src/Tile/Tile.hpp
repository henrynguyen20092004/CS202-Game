#ifndef TILE_HPP
#define TILE_HPP

#include "../SceneNode/SceneNode.hpp"

class Tile : public SceneNode {
   public:
    typedef std::unique_ptr<Tile> Ptr;

    enum Type { Good, Bad };
    // Good tiles are the ones that the player should step on
    // Bad tiles are the ones that the player should avoid

    Tile(Type type, sf::Vector2f position);

    Type getType() const;
    Directions::ID getDirection() const;
    sf::Vector2f getVelocity() const;

    void setDirection(Directions::ID direction);
    void setVelocity(sf::Vector2f velocity);

    float distanceTo(Tile* tile) const;

   private:
    Type mType;
    Directions::ID mDirection;
    sf::Vector2f mVelocity;

    virtual void updateCurrent(sf::Time deltaTime) override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const override;
};

#endif
