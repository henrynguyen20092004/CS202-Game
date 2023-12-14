#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../PlayerSettings/PlayerSettings.hpp"
#include "../SpriteNode/SpriteNode.hpp"

class Player : public SpriteNode {
   public:
    typedef std::unique_ptr<Player> Ptr;

    Player(
        TextureHolder& mTextureHolder, sf::View& worldView,
        PlayerSettings& playerSettings
    );

   private:
    PlayerSettings& mPlayerSettings;
    sf::View& mWorldView;
    std::map<Directions::ID, sf::Vector2f> mTargetDistance;

    const float mVelocity = 500.f;
    sf::Vector2f mTargetPosition;
    Directions::ID mDirection;
    bool mIsMoving;

    void handleEventCurrent(const sf::Event& event) override;

    void updateCurrent(sf::Time deltaTime) override;

    void initializeTargetDistance();
    void initializePosition(const sf::Vector2f& viewCenter);

    bool isOutOfBounds();

    void die();
};

#endif
