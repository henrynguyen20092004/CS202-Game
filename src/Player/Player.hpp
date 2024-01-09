#ifndef PLAYER_HPP
#define PLAYER_HPP

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

    bool askToMove();

    int getPlayerNumber() const;
    void setName(FontHolder& fontHolder);

    Directions::ID getDirection() const;
    Tile* getSourceTile() const;
    void setTargetTile(Tile* targetTile);

    int getMaxHealth() const;
    int getHealth() const;

    void setMaxHealth(int maxHealth);

    void addRevival();
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

    bool mIsImmortal = false;
    sf::Time mImmortalTime = sf::Time::Zero;

    Directions::ID mDirection = Directions::ID::None;
    Tile *mSourceTile = nullptr, *mTargetTile = nullptr;
    Halo* mHalo = nullptr;

    int mMaxHealth;
    int mHealth;

    bool mNeedToMove = false, mIsMoving = false, mForceGoGack = false,
         mHasRevival = false;

    bool isOutOfBounds() const;

    void handleEventCurrent(const sf::Event& event) override;
    void updateCurrent(sf::Time deltaTime) override;

    void saveCurrent(std::ofstream& fout) const final;
    void loadCurrent(std::ifstream& fin) final;
};

#endif
