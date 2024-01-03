#ifndef MAP_HPP
#define MAP_HPP

#include "../Lane/Lane.hpp"
#include "../Player/Player.hpp"

class Map : public SceneNode {
   public:
    typedef std::unique_ptr<Map> Ptr;

    Map(TextureHolder& textureHolder, sf::View& worldView, Player* player);

    bool isPlayerMoved() const;

    void handlePlayerCollision();

   private:
    TextureHolder& mTextureHolder;
    sf::View& mWorldView;
    std::deque<Lane*> mLanes;
    Player* mPlayer;
    bool mIsPlayerMoved;

    void initPlayer();
    int getPlayerLaneIndex() const;
    Tile* getPlayerNextTile(Directions::ID direction) const;
    void movePlayerTile(Tile* destinationTile);

    Lane* createLane(Textures::ID textureID, sf::Vector2f position);
    void initLanes();
    void addEmptyLane();
    void addRandomLane();
    void removeLane();

    void updateLanes();
    void updatePlayer();
    void updateCurrent(sf::Time deltaTime) override;
};

#endif
