#include "River.hpp"

#include "../../Global/Global.hpp"
#include "../../Log/LongLog/LongLog.hpp"
#include "../../Random/Random.hpp"

River::River(TextureHolder& textureHolder, const sf::Vector2f& position)
    : Lane(textureHolder, position) {
    buildScene();

    mDirection = Random<Directions::ID>::generate(
        {Directions::ID::Left, Directions::ID::Right}
    );

    mVelocity = sf::Vector2f(Random<float>::generate(100.f, 300.f), 0.f);

    init();
}

void River::buildScene() { Lane::buildScene(Textures::ID::River); }

Log* River::createLog(Textures::ID textureID) {
    switch (textureID) {
        case Textures::ID::LongLog:
            return new LongLog(mTextureHolder, mDirection);

        default:
            return nullptr;
    }
}

void River::init() {
    Log::Ptr log(createLog(Random<Textures::ID>::generate({Textures::ID::LongLog
    })));
    log->setVelocity(mVelocity);
    log->setPosition(
        mDirection == Directions::ID::Left ? -log->getSize().x
                                           : Global::WINDOW_WIDTH,
        (Global::TILE_SIZE - log->getSize().y) / 2.f
    );
    mLogs.push_front(log.get());
    mSceneLayers[ObjectLayer]->attachChild(std::move(log));
    mTileToNextSpawn = Random<int>::generate(2, 10);
}

void River::addLog() {
    Log::Ptr log(createLog(Random<Textures::ID>::generate({Textures::ID::LongLog
    })));
    log->setVelocity(mVelocity);
    log->setPosition(
        mDirection == Directions::ID::Left
            ? mLogs.front()->getPosition().x + mLogs.front()->getSize().x +
                  mTileToNextSpawn * Global::TILE_SIZE
            : mLogs.front()->getPosition().x -
                  mTileToNextSpawn * Global::TILE_SIZE - log->getSize().x,
        (Global::TILE_SIZE - log->getSize().y) / 2.f
    );
    mLogs.push_front(log.get());
    mSceneLayers[ObjectLayer]->attachChild(std::move(log));
}

void River::removeLog() {
    mSceneLayers[ObjectLayer]->detachChild(*mLogs.back());
    mLogs.pop_back();
}

void River::updateCurrent(sf::Time deltaTime) {
    if (mLogs.empty()) {
        return;
    }

    while ((mDirection == Directions::ID::Left &&
            mLogs.front()->getPosition().x + mLogs.front()->getSize().x <
                Global::WINDOW_WIDTH - mTileToNextSpawn * Global::TILE_SIZE) ||
           (mDirection == Directions::ID::Right &&
            mLogs.front()->getPosition().x >
                mTileToNextSpawn * Global::TILE_SIZE)) {
        addLog();
        mTileToNextSpawn = Random<int>::generate(2, 10);
    }

    if (mDirection == Directions::ID::Left) {
        if (mLogs.back()->getPosition().x < -mLogs.back()->getSize().x) {
            removeLog();
        }
    } else {
        if (mLogs.back()->getPosition().x > Global::WINDOW_WIDTH) {
            removeLog();
        }
    }
}
