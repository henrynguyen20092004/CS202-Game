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

    float distanceTo(const Tile& other) const;

   private:
    Type mType;

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const override;
};

#endif
