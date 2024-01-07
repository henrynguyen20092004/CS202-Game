#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Blood/Blood.hpp"
#include "../Entity/Entity.hpp"
#include "../Halo/Halo.hpp"
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
    bool isImmortal() const;
    bool isRegenerate() const;

    void setTargetTile(Tile* targetTile);

    void setImmortalTime(sf::Time immortalTime);

    void addRegenerate();
    void kill();
    void damage();
    void heal();
    void goBack();

    void setScorePtr(Score* score);
    void addBonusScore() const;

    bool isAlive();

    void handlePlayerCollision(Player& player) override;

   private:
    PlayerSettings& mPlayerSettings;
    sf::View& mWorldView;
    Score* mScore = nullptr;
    Halo* mHalo = nullptr;

    sf::Time mImmortalTime, mRegenerateTime;

    Directions::ID mDirection = Directions::ID::None;
    Tile *mSourceTile = nullptr, *mTargetTile = nullptr;

    bool mNeedToMove = false, mIsMoving = false, mForceGoGack = false,
         mHasRegenerate = false;
    

    int mHealth = 60;
    Blood* mBlood;

   

    void handleEventCurrent(const sf::Event& event) override;
    void updateCurrent(sf::Time deltaTime) override;

    bool isOutOfBounds() const;
};

#endif
