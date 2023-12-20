#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "../Animation/Animation.hpp"
#include "../PowerUpList/PowerUpList.hpp"
#include "../SpriteNode/SpriteNode.hpp"

class Animal : public SpriteNode {
   public:
    typedef std::unique_ptr<Animal> Ptr;

    Animal(
        TextureHolder& TextureHolder, Textures::ID textureID,
        PowerUpList& powerUpList, int numFrames, sf::Time duration
    );

   private:
    PowerUpList& mPowerUpList;
    Animation mAnimation;

    void initPosition();

    void onPlayerCollision(Player& player) override;

    void updateCurrent(sf::Time deltaTime) override;

    virtual PowerUp::Type getPowerUpType() const = 0;
};

#endif
