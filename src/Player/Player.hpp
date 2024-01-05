#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Entity/Entity.hpp"
#include "../PlayerSettings/PlayerSettings.hpp"
#include "../Tile/Tile.hpp"

class Score;

class Player : public Entity {
   public:
    typedef std::unique_ptr<Player> Ptr;

    Player(
        TextureHolder& mTextureHolder, Textures::ID textureID,
        sf::View& worldView, PlayerSettings& playerSettings
    );

    bool askToMove();
    Directions::ID getDirection() const;
    Tile* getSourceTile() const;
    Tile* getTargetTile() const;

    void setTargetTile(Tile* targetTile);

    void kill();
    void damage();
    void heal();
    void goBack();

    void setScorePtr(Score* score);
    void addBonusScore() const;

    bool isAlive() const;

    void handlePlayerCollision(Player& player) override;

   private:
    PlayerSettings& mPlayerSettings;
    sf::View& mWorldView;
    Score* mScore = nullptr;

    Directions::ID mDirection = Directions::ID::None;
    Tile *mSourceTile = nullptr, *mTargetTile = nullptr;
    bool mNeedToMove = false, mIsMoving = false, mForceGoGack = false;

    int mHealth = 1;

    void handleEventCurrent(const sf::Event& event) override;
    void updateCurrent(sf::Time deltaTime) override;

    bool isOutOfBounds() const;
};

#endif
