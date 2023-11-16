#ifndef ELEPHANT_HPP
#define ELEPHANT_HPP

#include"../Animal.hpp"
#include "../../ResourceHolder/ResourceHolder.hpp"

class Elephant : public Animal {
   public:
    Elephant(const sf::Vector2f& position,TextureHolder& textureHolder);

    ~Elephant();
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    //void update(float dt);
};

#endif  // ELEPHANT_HPP