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

    void damage();
    void heal();
    bool isAlive() const;

   private:
    PlayerSettings& mPlayerSettings;
    sf::View& mWorldView;
    std::map<Directions::ID, sf::Vector2f> mTargetDistance;

    sf::Vector2f mTargetPosition;
    const float mVelocity = 500.f;
    bool mIsMoving;

    int mHealth = 1;

    void handleEventCurrent(const sf::Event& event) override;
    void updateCurrent(sf::Time deltaTime) override;

    void initPosition(const sf::Vector2f& viewCenter);
    void initTargetDistance();

    bool isOutOfBounds();
    void dieOutofBounds();
};

#endif
