#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "../Identifier/Identifier.hpp"

class Vehicle : public sf::Drawable, public sf::Transformable {
   public:
    typedef std::unique_ptr<Vehicle> Ptr;

    Directions::ID getDirection() const;
    float getSpeed() const;

    void setDirection(Directions::ID direction);
    void setSpeed(float speed);

    void update(float deltaTime);

   protected:
    sf::Sprite mSprite;

    Vehicle(Directions::ID direction, float speed);

   private:
    Directions::ID mDirection;
    float mSpeed;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
