#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <SFML/Graphics.hpp>
#include <memory>

class Animal : public sf::Drawable, public sf::Transformable {
   public:
    typedef std::unique_ptr<Animal> Ptr;

    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    void setDirection(int direction);
    int getDirection() const;
    void setSpeed(float speed);
    float getSpeed() const;

   protected:
    sf::Vector2f mPosition;
    int mDirection;
    float mSpeed;

    Animal(const sf::Vector2f& position, int direction, float speed);
    ~Animal();

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
