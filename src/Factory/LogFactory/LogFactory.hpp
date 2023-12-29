#ifndef LOG_FACTORY_HPP
#define LOG_FACTORY_HPP

#include <queue>

#include "../../Log/Log.hpp"
#include "../Factory.hpp"

class LogFactory : public Factory {
   public:
    typedef std::unique_ptr<LogFactory> Ptr;

    LogFactory(TextureHolder& textureHolder);

   private:
    Directions::ID mDirection;
    sf::Vector2f mVelocity;
    int mTileToNextSpawn;
    std::deque<Log*> mLogs;

    Log* createLog(Textures::ID textureID);
    void init() override;

    void addLog();
    void removeLog();

    void updateCurrent(sf::Time deltaTime) override;
};

#endif
