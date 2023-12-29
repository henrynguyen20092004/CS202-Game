#ifndef LANE_HPP
#define LANE_HPP

#include <array>

#include "../Factory/Factory.hpp"
#include "../Tile/Tile.hpp"

class Lane : public SceneNode {
   public:
    typedef std::unique_ptr<Lane> Ptr;

    Lane(TextureHolder& textureHolder, const sf::Vector2f& position);

    virtual void handlePlayerCollision(Player& player);

   protected:
    TextureHolder& mTextureHolder;

    enum Layer {
        LaneLayer,
        FactoryLayer,
        TileLayer,
        TrafficLightLayer,
        LayerCount,
    };

    std::array<SceneNode*, LayerCount> mSceneLayers;
    std::vector<Tile*> mLaneTiles, mLogTiles;

    void buildScene(Textures::ID textureID);
};

#endif
