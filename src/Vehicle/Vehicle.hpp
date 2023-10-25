#ifndef VEHIHLE_HPP
#define VEHICLE_HPP

#include <SFML/Graphics.hpp>

class Vehicle : public sf::Drawable, public sf::Transformable {
   public:
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const;
    void setDirection(int direction);
    int getDirection() const;
    void setSpeed(float speed);
    float getSpeed() const;

    virtual void update(float dt) = 0;

   protected:
    Vehicle(sf::Vector2f position, int direction, float speed);
    ~Vehicle();

    sf::Vector2f mPosition;
    int mDirection;
    float mSpeed;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif