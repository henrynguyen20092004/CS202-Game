#include "River.hpp"

#include "../../Global/Global.hpp"
#include "../../Log/LongLog/LongLog.hpp"
#include "../../Log/MediumLog/MediumLog.hpp"
#include "../../Log/ShortLog/ShortLog.hpp"
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
        case Textures::ID::ShortLog:
            return new ShortLog(mTextureHolder, mDirection);

        case Textures::ID::MediumLog:
            return new MediumLog(mTextureHolder, mDirection);

        case Textures::ID::LongLog:
            return new LongLog(mTextureHolder, mDirection);

        default:
            return nullptr;
    }
}

void River::init() {
    mTileToNextSpawns.push_front(0);

    Log::Ptr log(
        createLog(Random<Textures::ID>::generate({Textures::ID::ShortLog}))
    );
    log->setVelocity(mVelocity);
    sf::Vector2f position = sf::Vector2f(
        mDirection == Directions::ID::Left ? -log->getSize().x
                                           : Global::WINDOW_WIDTH,
        0.f
    );
    log->setPosition(position);
    mLogs.push_front(log.get());
    mSceneLayers[ObjectLayer]->attachChild(std::move(log));
    mTileToNextSpawns.push_front(Random<int>::generate(2, 10));

    for (int i = 0; i < mLogs.front()->getLength(); ++i) {
        Tile::Ptr tile(new Tile(
            Tile::Type::Good,
            position + sf::Vector2f(i * Global::TILE_SIZE, 0.f)
        ));
        tile->setDirection(mDirection);
        tile->setVelocity(mVelocity);
        mLaneTiles.push_front(tile.get());
        mSceneLayers[TileLayer]->attachChild(std::move(tile));
    }

    for (int i = 0; i < mTileToNextSpawns.front(); ++i) {
        Tile::Ptr tile(new Tile(
            Tile::Type::Bad,
            position +
                sf::Vector2f(
                    mDirection == Directions::ID::Left
                        ? (i + mLogs.front()->getLength()) * Global::TILE_SIZE
                        : -(i + 1) * Global::TILE_SIZE,
                    0.f
                )
        ));
        tile->setDirection(mDirection);
        tile->setVelocity(mVelocity);
        mLaneTiles.push_front(tile.get());
        mSceneLayers[TileLayer]->attachChild(std::move(tile));
    }
}

void River::addLog() {
    Log::Ptr log(createLog(Random<Textures::ID>::generate(
        {Textures::ID::ShortLog, Textures::ID::MediumLog, Textures::ID::LongLog}
    )));
    log->setVelocity(mVelocity);
    sf::Vector2f position = sf::Vector2f(
        mDirection == Directions::ID::Left
            ? mLogs.front()->getPosition().x + mLogs.front()->getSize().x +
                  mTileToNextSpawns.front() * Global::TILE_SIZE
            : mLogs.front()->getPosition().x -
                  mTileToNextSpawns.front() * Global::TILE_SIZE -
                  log->getSize().x,
        (Global::TILE_SIZE - log->getSize().y) / 2.f
    );
    log->setPosition(position);
    mLogs.push_front(log.get());
    mSceneLayers[ObjectLayer]->attachChild(std::move(log));
    mTileToNextSpawns.push_front(Random<int>::generate(2, 10));

    for (int i = 0; i < mLogs.front()->getLength(); ++i) {
        Tile::Ptr tile(new Tile(
            Tile::Type::Good,
            position + sf::Vector2f(i * Global::TILE_SIZE, 0.f)
        ));
        tile->setDirection(mDirection);
        tile->setVelocity(mVelocity);
        mLaneTiles.push_front(tile.get());
        mSceneLayers[TileLayer]->attachChild(std::move(tile));
    }

    for (int i = 0; i < mTileToNextSpawns.front(); ++i) {
        Tile::Ptr tile(new Tile(
            Tile::Type::Bad,
            position +
                sf::Vector2f(
                    mDirection == Directions::ID::Left
                        ? (i + mLogs.front()->getLength()) * Global::TILE_SIZE
                        : -(i + 1) * Global::TILE_SIZE,
                    0.f
                )
        ));
        tile->setDirection(mDirection);
        tile->setVelocity(mVelocity);
        mLaneTiles.push_front(tile.get());
        mSceneLayers[TileLayer]->attachChild(std::move(tile));
    }
}

void River::removeLog() {
    for (int i = 0; i < mTileToNextSpawns.back(); ++i) {
        mSceneLayers[TileLayer]->detachChild(*mLaneTiles.back());
        mLaneTiles.pop_back();
    }

    mTileToNextSpawns.pop_back();

    for (int i = 0; i < mLogs.back()->getLength(); ++i) {
        mSceneLayers[TileLayer]->detachChild(*mLaneTiles.back());
        mLaneTiles.pop_back();
    }

    mSceneLayers[ObjectLayer]->detachChild(*mLogs.back());
    mLogs.pop_back();
}

void River::updateCurrent(sf::Time deltaTime) {
    if (mLogs.empty()) {
        return;
    }

    while ((mDirection == Directions::ID::Left &&
            mLogs.front()->getPosition().x + mLogs.front()->getSize().x <
                Global::WINDOW_WIDTH -
                    mTileToNextSpawns.front() * Global::TILE_SIZE) ||
           (mDirection == Directions::ID::Right &&
            mLogs.front()->getPosition().x >
                mTileToNextSpawns.front() * Global::TILE_SIZE)) {
        addLog();
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
