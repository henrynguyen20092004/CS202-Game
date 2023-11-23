#ifndef ELEPHANT_HPP
#define ELEPHANT_HPP

#include "../Animal.hpp"
class Elephant: public Animal {
   public:
    Elephant(const sf::Texture& texture);
    virtual ~Elephant() = default;

   private:
    virtual void updateCurrent(float deltaTime) override;
};

#endif