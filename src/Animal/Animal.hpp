#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "../Identifier/Identifier.hpp"

class Animal : public sf::Drawable, public sf::Transformable {
   public:
    typedef std::unique_ptr<Animal> Ptr;

    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    

   protected:
    sf::Vector2f mPosition;
    sf::Sprite mSprite;

    Animal(const sf::Vector2f& position);
    ~Animal();

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
