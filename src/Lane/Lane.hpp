#ifndef LANE_HPP
#define LANE_HPP

#include <array>
#include <queue>

#include "../ResourceHolder/ResourceHolder.hpp"
#include "../Tile/Tile.hpp"

class Lane : public SceneNode {
   public:
    typedef std::unique_ptr<Lane> Ptr;

    Lane(
        TextureHolder& textureHolder, int seasonIndex,
        const sf::Vector2f& position
    );

    Tile* getTile(int index) const;
    Tile* getNearestTile(Tile* tile, Tile::Type type, Directions::ID direction)
        const;
    Tile* getPlayerTile(float playerWorldPosX) const;

    virtual void handlePlayerCollision(Player& player);

   protected:
    enum Layer {
        LaneLayer,
        ObjectLayer,
        SignalLightLayer,
        TileLayer,
        LayerCount,
    };

    TextureHolder& mTextureHolder;
    int mSeasonIndex;

    std::array<SceneNode*, LayerCount> mSceneLayers;
    std::deque<Tile*> mLaneTiles;

    void buildScene(Textures::ID textureID, bool isLoading);

    void saveCurrent(std::ofstream& fout) const override;
    void loadCurrent(std::ifstream& fin) override;
};

#endif
