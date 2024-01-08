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
        TextureHolder& textureHolder, Textures::ID textureID,
        sf::View& worldView, PlayerSettings& playerSettings, int playerNumber
    );

    int getPlayerNumber() const;
    void setName(FontHolder& fontHolder);

    bool askToMove();
    Directions::ID getDirection() const;
    Tile* getSourceTile() const;
    Tile* getTargetTile() const;
    void setTargetTile(Tile* targetTile);

    int getMaxHealth() const;
    int getHealth() const;

    void addRevival();
    void addBonusScore() const;
    void addHealth();

    bool isImmortal() const;
    void setImortal(bool isImmortal);

    void kill();
    void damage();
    void goBack();

    bool isAlive();

    void handlePlayerCollision(Player& player) override;

   private:
    PlayerSettings& mPlayerSettings;
    sf::View& mWorldView;
    int mPlayerNumber;

    Score* mScore = nullptr;
    Halo* mHalo = nullptr;

    bool mIsImmortal = false;
    sf::Time mImmortalTime = sf::Time::Zero;

    Directions::ID mDirection = Directions::ID::None;
    Tile *mSourceTile = nullptr, *mTargetTile = nullptr;

    bool mNeedToMove = false, mIsMoving = false, mForceGoGack = false,
         mHasRevival = false;

    const int mMaxHealth = 100;
    int mHealth = mMaxHealth;

    void handleEventCurrent(const sf::Event& event) override;
    void updateCurrent(sf::Time deltaTime) override;

    bool isOutOfBounds() const;
};

#endif
