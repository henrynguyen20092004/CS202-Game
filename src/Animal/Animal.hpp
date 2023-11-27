#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "../Identifier/Identifier.hpp"
#include "../MovableSpriteNode/MovableSpriteNode.hpp"

class Animal : public MovableSpriteNode {
   public:
    typedef std::unique_ptr<Animal> Ptr;

   protected:
    Animal(const sf::Texture& texture);
    virtual void updateCurrent(float deltaTime) = 0;
    // virtual void powerUp() = 0;
};

#endif
