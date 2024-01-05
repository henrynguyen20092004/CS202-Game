#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Entity/Entity.hpp"
#include "../PlayerSettings/PlayerSettings.hpp"
#include "../Tile/Tile.hpp"
#include "../Blood/Blood.hpp"
class Score;

class Player : public Entity {
   public:
    typedef std::unique_ptr<Player> Ptr;

    Player(
        TextureHolder& mTextureHolder, sf::View& worldView,
        PlayerSettings& playerSettings
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

   private:
    PlayerSettings& mPlayerSettings;
    sf::View& mWorldView;
    Score* mScore = nullptr;

    Directions::ID mDirection = Directions::ID::None;
    Tile *mSourceTile = nullptr, *mTargetTile = nullptr;
    bool mNeedToMove = false, mIsMoving = false, mForceGoGack = false;

    int mHealth = 1;
    Blood* mBlood;
    void initPosition(const sf::Vector2f& viewCenter);
    void initTargetDistance();

    void handleEventCurrent(const sf::Event& event) override;
    void updateCurrent(sf::Time deltaTime) override;

    bool isOutOfBounds() const;
};

#endif
