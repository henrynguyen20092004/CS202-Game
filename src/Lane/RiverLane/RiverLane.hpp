#ifndef RIVER_LANE_HPP
#define RIVER_LANE_HPP

#include "../../Log/Log.hpp"
#include "../Lane.hpp"

class RiverLane : public Lane {
   public:
    RiverLane(
        TextureHolder& textureHolder, const sf::Vector2f& position,
        bool isLoading
    );

   private:
    Directions::ID mDirection;
    sf::Vector2f mVelocity;
    std::deque<Log*> mLogs;
    std::deque<int> mTileToNextSpawns;

    void buildScene(bool isLoading);

    void init();

    Log* createLog(Textures::ID textureID);
    void addLogTiles(const sf::Vector2f& logPosition);
    void addLog();
    void removeLog();

    Textures::ID getTextureID() const final;

    void updateCurrent(sf::Time deltaTime) override;

    void saveCurrent(std::ofstream& fout) const final;
    void loadCurrent(std::ifstream& fin) final;
};

#endif
