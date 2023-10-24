#ifndef VEHIHLE_HPP
#define VEHICLE_HPP

#include <SFML/Graphics.hpp>

class Vehicle : public sf::Drawable, public sf::Transformable {
   public:
    sf::Vector2f getPosition() const;

    virtual void update(float dt) = 0;

   protected:
    Vehicle(sf::Vector2f position, int direction, float speed);
    ~Vehicle();

    sf::Vector2f mPosition;
    int mDirection;
    float mSpeed;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif  // VEHICLE_HPP