#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "../Entity/Entity.hpp"

class Vehicle : public Entity {
   public:
    typedef std::unique_ptr<Vehicle> Ptr;

    void handlePlayerCollision(Player& player) override;

   protected:
    Vehicle(
        TextureHolder& textureHolder, Textures::ID textureID,
        sf::IntRect textureRect, Directions::ID direction
    );

   private:
    Directions::ID mDirection;

    void updateCurrent(sf::Time deltaTime) override;

    void saveCurrent(std::ofstream& fout) const final;
    void loadCurrent(std::ifstream& fin) final;
};

#endif
