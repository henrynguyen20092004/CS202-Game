#ifndef MAP_HPP
#define MAP_HPP

#include "../Lane/Lane.hpp"
#include "../Player/Player.hpp"
#include "../PowerUpList/PowerUpList.hpp"
#include "../Score/Score.hpp"

class Map : public SceneNode {
   public:
    typedef std::unique_ptr<Map> Ptr;

    Map(TextureHolder& textureHolder, sf::View& worldView,
        const std::vector<Player*>& players,
        const std::vector<PowerUpList*>& powerUpList, Score* score,
        bool isLoading);

    bool isPlayerMoved() const;

    void handlePlayerCollision();

    Tile* getPlayerTile(int playerIndex) const;

   private:
    TextureHolder& mTextureHolder;
    sf::View& mWorldView;
    Score* mScore;
    std::deque<Lane*> mLanes;
    std::vector<Player*> mPlayers;
    std::vector<PowerUpList*> mPowerUpList;
    bool mIsPlayerMoved = false;

    void initPlayer();

    int getPlayerLaneIndex(int playerIndex) const;
    Tile* getPlayerNextTile(int playerIndex, Directions::ID direction) const;
    void movePlayerTile(int playerIndex, Tile* destinationTile);

    Lane* createLane(
        Textures::ID textureID, sf::Vector2f position, bool isLoading
    );
    void initLanes();
    void addEmptyLane();
    void addRandomLane();
    void removeLane();

    void updateLanes();
    void updatePlayer();
    void updateCurrent(sf::Time deltaTime) override;

    void saveCurrent(std::ofstream& fout) const final;
    void loadCurrent(std::ifstream& fin) final;
};

#endif
