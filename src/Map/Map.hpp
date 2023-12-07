#ifndef MAP_HPP
#define MAP_HPP

#include <queue>

#include "../Lane/Lane.hpp"

class Map : public SceneNode {
   public:
    Map(TextureHolder& textureHolder, sf::View& worldView);

   private:
    TextureHolder& mTextureHolder;
    sf::View& mWorldView;
    std::deque<Lane*> mLanes;

    void addLane();
    void removeLane();

    void updateCurrent(sf::Time deltaTime) override;
};

#endif
