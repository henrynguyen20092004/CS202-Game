#ifndef POWER_UP_ICON_HPP
#define POWER_UP_ICON_HPP

#include "../SpriteNode/SpriteNode.hpp"
#include "../TextNode/TextNode.hpp"

struct PowerUpIconArgs {
    PowerUpIconArgs(
        TextureHolder& textureHolder, FontHolder& fontHolder,
        sf::View& worldView, sf::Vector2f positionOffset
    );

    TextureHolder& textureHolder;
    FontHolder& fontHolder;
    sf::View& worldView;
    sf::Vector2f& positionOffset;
};

class PowerUpIcon : public SpriteNode {
   public:
    typedef std::unique_ptr<PowerUpIcon> Ptr;

    PowerUpIcon(
        const PowerUpIconArgs& powerUpIconArgs, Textures::ID textureID,
        int& count
    );

   private:
    TextNode* mTextNode;
    sf::Vector2f mPositionOffset;
    sf::View& mWorldView;
    int& mCount;

    void updateCurrent(sf::Time deltaTime) override;
};

#endif
