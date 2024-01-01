#ifndef LANE_HPP
#define LANE_HPP

#include <array>
#include <queue>

#include "../ResourceHolder/ResourceHolder.hpp"
#include "../Tile/Tile.hpp"

class Lane : public SceneNode {
   public:
    typedef std::unique_ptr<Lane> Ptr;

    Lane(TextureHolder& textureHolder, const sf::Vector2f& position);

    Tile* getTile(int index) const;
    Tile* getNearestTile(Tile* tile, Tile::Type type, Directions::ID direction)
        const;

    virtual void handlePlayerCollision(Player& player);

   protected:
    TextureHolder& mTextureHolder;

    enum Layer {
        LaneLayer,
        ObjectLayer,
        TrafficLightLayer,
        TileLayer,
        LayerCount,
    };

    std::array<SceneNode*, LayerCount> mSceneLayers;
    std::deque<Tile*> mLaneTiles;

    void buildScene(Textures::ID textureID);
};

#endif
