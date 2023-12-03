#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "../Identifier/Identifier.hpp"
#include "../MovableSpriteNode/MovableSpriteNode.hpp"

class Vehicle : public MovableSpriteNode {
   public:
    typedef std::unique_ptr<Vehicle> Ptr;

    Vehicle(
        TextureHolder& textureHolder, Textures::ID texureID,
        Directions::ID direction
    );

    Directions::ID getDirection() const;

    void setDirection(Directions::ID direction);

   private:
    Directions::ID mDirection;

    void updateCurrent(sf::Time deltaTime) override;
};

#endif
