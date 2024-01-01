#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Entity/Entity.hpp"
#include "../PlayerSettings/PlayerSettings.hpp"
#include "../Tile/Tile.hpp"

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

    bool isAlive() const;

   private:
    PlayerSettings& mPlayerSettings;
    sf::View& mWorldView;

    Directions::ID mDirection;
    Tile* mSourceTile;
    Tile* mTargetTile;
    bool mNeedToMove, mIsMoving;

    bool mForceGoGack;

    int mHealth = 1;

    void handleEventCurrent(const sf::Event& event) override;
    void updateCurrent(sf::Time deltaTime) override;

    bool isOutOfBounds() const;
};

#endif
