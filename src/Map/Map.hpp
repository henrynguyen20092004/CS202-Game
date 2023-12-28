#ifndef MAP_HPP
#define MAP_HPP

#include <queue>

#include "../Lane/Lane.hpp"

class Map : public SceneNode {
   public:
    typedef std::unique_ptr<Map> Ptr;

    Map(TextureHolder& textureHolder, sf::View& worldView);

    void handlePlayerCollision(Player& player);

   private:
    TextureHolder& mTextureHolder;
    sf::View& mWorldView;
    std::deque<Lane*> mLanes;

    Lane* makeLane(Textures::ID textureID, sf::Vector2f position);

    void addEmptyLane();
    void addRandomLane();
    void removeLane();

    void updateCurrent(sf::Time deltaTime) override;
};

#endif
