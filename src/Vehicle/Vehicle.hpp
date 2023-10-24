#ifndef VEHIHLE_HPP
#define VEHICLE_HPP

#include <SFML/Graphics.hpp>

class Vehicle : public sf::Drawable, public sf::Transformable {
   public:
    int getX() const;
    int getY() const;

    virtual void update(float dt) = 0;

   protected:
    Vehicle(float x, float y, int direction, float speed);
    ~Vehicle();

    float mX;
    float mY;
    int mDirection;
    float mSpeed;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif  // VEHICLE_HPP