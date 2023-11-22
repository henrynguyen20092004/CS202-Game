#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "../MovableSpriteNode/MovableSpriteNode.hpp"

class Animal : public MovableSpriteNode {
   public:
    typedef std::unique_ptr<Animal> Ptr;

   protected:
    Animal(const sf::Texture& texture);

    virtual void updateCurrent(float deltaTime) = 0;
};

#endif
