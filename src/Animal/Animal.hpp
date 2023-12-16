#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "../SpriteNode/SpriteNode.hpp"
#include "../PowerUpList/PowerUpList.hpp"

class Animal : public SpriteNode {
   public:
    Animal(
        TextureHolder& TextureHolder, Textures::ID textureID,
        sf::View& worldView, PowerUpList& powerUpList
    );

   private:
    sf::View& mWorldView;
    PowerUpList& mPowerUpList;

    void initPosition(const sf::Vector2f& viewCenter);

    void onPlayerCollision(Player& player) override;

    virtual PowerUp::Type getPowerUpType() const = 0;
};

#endif
