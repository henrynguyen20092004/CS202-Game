#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "../Entity/Entity.hpp"

class Vehicle : public Entity {
   public:
    typedef std::unique_ptr<Vehicle> Ptr;

    Directions::ID getDirection() const;
    void setDirection(Directions::ID direction);

    void handlePlayerCollision(Player& player) override;

   protected:
    Vehicle(
        TextureHolder& textureHolder, Textures::ID textureID,
        Directions::ID direction
    );

   private:
    Directions::ID mDirection;

    void updateCurrent(sf::Time deltaTime) override;
};

#endif
