#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "../ResourceHolder/ResourceHolder.hpp"

/*
    TODO: create obstacle in tile map with random/given position
*/

class Obstacle : public sf::Drawable, public sf::Transformable {
   public:
    typedef std::unique_ptr<Obstacle> Ptr;

    sf::Vector2f getSize() const;

    void setSize(const sf::Vector2f& size);

    virtual void update(float deltaTime) = 0;

    bool isColliding(const sf::FloatRect& otherHitBox) const;

   protected:
    Obstacle(const sf::Vector2f& size);
    ~Obstacle();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   private:
    sf::Vector2f mSize;
};

#endif
