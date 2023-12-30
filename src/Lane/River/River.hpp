#ifndef RIVER_HPP
#define RIVER_HPP

#include "../../Log/Log.hpp"
#include "../Lane.hpp"

class River : public Lane {
   public:
    River(TextureHolder& textureHolder, const sf::Vector2f& position);

   private:
    Directions::ID mDirection;
    sf::Vector2f mVelocity;
    std::deque<Log*> mLogs;
    std::deque<int> mTileToNextSpawns;

    void buildScene();

    Log* createLog(Textures::ID textureID);
    void init();
    void addLog();
    void removeLog();

    void updateCurrent(sf::Time deltaTime) override;
};

#endif
