#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "../Entity/Entity.hpp"

class Vehicle : public Entity {
   public:
    typedef std::unique_ptr<Vehicle> Ptr;

   protected:
    Vehicle(TextureHolder& textureHolder, Directions::ID direction);

   public:
    Directions::ID getDirection() const;
    void setDirection(Directions::ID direction);

    void handlePlayerCollision(Player& player) override;

   private:
    Directions::ID mDirection;

    void updateCurrent(sf::Time deltaTime) override;
};

#endif
