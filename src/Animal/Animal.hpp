#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "../Animation/Animation.hpp"
#include "../Entity/Entity.hpp"
#include "../PowerUpList/PowerUpList.hpp"

class Animal : public Entity {
   public:
    typedef std::unique_ptr<Animal> Ptr;

    Animal(
        TextureHolder& TextureHolder, Textures::ID textureID,
        PowerUpList& powerUpList, int numFrames, sf::Time duration
    );

    virtual void handlePlayerCollision(Player& player) override;

   private:
    PowerUpList& mPowerUpList;
    Animation mAnimation;

    void initPosition();

    virtual PowerUp::Type getPowerUpType() const = 0;

    virtual void updateCurrent(sf::Time deltaTime) override;
};

#endif
