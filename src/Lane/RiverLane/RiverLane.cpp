#include "RiverLane.hpp"

#include "../../FileIO/FileIO.hpp"
#include "../../Global/Global.hpp"
#include "../../Log/LongLog/LongLog.hpp"
#include "../../Log/MediumLog/MediumLog.hpp"
#include "../../Log/ShortLog/ShortLog.hpp"
#include "../../Random/Random.hpp"

RiverLane::RiverLane(
    TextureHolder& textureHolder, const sf::Vector2f& position, bool isLoading
)
    : Lane(textureHolder, position) {
    buildScene(isLoading);

    if (isLoading) {
        return;
    }

    mDirection = Random<Directions::ID>::generate(
        {Directions::ID::Left, Directions::ID::Right}
    );

    mVelocity = sf::Vector2f(
        static_cast<Seasons::ID>(Global::SEASON_INDEX) == Seasons::ID::Winter
            ? 0
            : Random<float>::generate(250.f, 300.f),
        0.f
    );

    init();
}

void RiverLane::buildScene(bool isLoading) {
    Lane::buildScene(Textures::ID::RiverLane, isLoading);

    for (int i = 0; i < Global::NUM_TILES_X; ++i) {
        SpriteNode::Ptr sprite(new SpriteNode(
            mTextureHolder, Textures::ID::RiverLane,
            sf::IntRect(
                Random<int>::generate({0, 1, 2}, {90, 5, 5}) *
                    Global::TILE_SIZE,
                Global::SEASON_INDEX * Global::TILE_SIZE, Global::TILE_SIZE,
                Global::TILE_SIZE
            )
        ));
        sprite->setPosition(i * Global::TILE_SIZE, 0.f);
        mSceneLayers[LaneLayer]->attachChild(std::move(sprite));
    }
}

void RiverLane::init() {
    mTileToNextSpawns.push_front(0);

    Log::Ptr log(
        createLog(Random<Textures::ID>::generate({Textures::ID::ShortLog}))
    );
    sf::Vector2f position(
        mDirection == Directions::ID::Left ? -log->getSize().x
                                           : Global::WINDOW_WIDTH,
        0.f
    );

    log->setVelocity(mVelocity);
    log->setPosition(position);
    mLogs.push_front(log.get());
    mSceneLayers[ObjectLayer]->attachChild(std::move(log));
    mTileToNextSpawns.push_front(Random<int>::generate(0, 5));

    addLogTiles(position);
}

Log* RiverLane::createLog(Textures::ID textureID) {
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

void RiverLane::addLogTiles(const sf::Vector2f& logPosition) {
    for (int i = 0; i < mLogs.front()->getLength(); ++i) {
        Tile::Ptr tile(new Tile(
            Tile::Type::Good,
            logPosition + sf::Vector2f(i * Global::TILE_SIZE, 0.f), mDirection
        ));
        tile->setVelocity(mVelocity);
        mLaneTiles.push_front(tile.get());
        mSceneLayers[TileLayer]->attachChild(std::move(tile));
    }

    for (int i = 0; i < mTileToNextSpawns.front(); ++i) {
        Tile::Ptr tile(new Tile(
            static_cast<Seasons::ID>(Global::SEASON_INDEX) ==
                    Seasons::ID::Winter
                ? Tile::Type::Good
                : Tile::Type::Bad,
            logPosition +
                sf::Vector2f(
                    Global::TILE_SIZE * (mDirection == Directions::ID::Left
                                             ? (i + mLogs.front()->getLength())
                                             : -(i + 1)),
                    0.f
                ),
            mDirection
        ));
        tile->setVelocity(mVelocity);
        mLaneTiles.push_front(tile.get());
        mSceneLayers[TileLayer]->attachChild(std::move(tile));
    }
}

void RiverLane::addLog() {
    float frontLogPosX = mLogs.front()->getPosition().x;
    Log::Ptr log(createLog(Random<Textures::ID>::generate(
        {Textures::ID::ShortLog, Textures::ID::MediumLog, Textures::ID::LongLog
        },
        {20, 40, 40}
    )));
    sf::Vector2f position(
        mDirection == Directions::ID::Left
            ? frontLogPosX + mLogs.front()->getSize().x +
                  mTileToNextSpawns.front() * Global::TILE_SIZE
            : frontLogPosX - mTileToNextSpawns.front() * Global::TILE_SIZE -
                  log->getSize().x,
        (Global::TILE_SIZE - log->getSize().y) / 2.f
    );

    log->setVelocity(mVelocity);
    log->setPosition(position);
    mLogs.push_front(log.get());
    mSceneLayers[ObjectLayer]->attachChild(std::move(log));
    mTileToNextSpawns.push_front(Random<int>::generate(1, 5));

    addLogTiles(position);
}

void RiverLane::removeLog() {
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

Textures::ID RiverLane::getTextureID() const { return Textures::ID::RiverLane; }

void RiverLane::updateCurrent(sf::Time deltaTime) {
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

    float backLogPosX = mLogs.back()->getPosition().x;

    if (mDirection == Directions::ID::Left &&
            backLogPosX < -mLogs.back()->getSize().x - Global::TILE_SIZE ||
        mDirection == Directions::ID::Right &&
            backLogPosX > Global::WINDOW_WIDTH + Global::TILE_SIZE) {
        removeLog();
    }
}

void RiverLane::saveCurrent(std::ofstream& fout) const {
    Lane::saveCurrent(fout);
    int numLogs = mLogs.size(), numTileToNextSpawns = mTileToNextSpawns.size();

    fout << static_cast<int>(mDirection) << '\n';
    fout << mVelocity << '\n';
    fout << numLogs << '\n';

    for (int i = numLogs - 1; i >= 0; --i) {
        fout << static_cast<int>(mLogs[i]->getTextureID()) << (i ? ' ' : '\n');
    }

    fout << numTileToNextSpawns << '\n';

    for (int i = numTileToNextSpawns - 1; i >= 0; --i) {
        fout << mTileToNextSpawns[i] << (i ? ' ' : '\n');
    }
}

void RiverLane::loadCurrent(std::ifstream& fin) {
    Lane::loadCurrent(fin);
    int direction, numLogs, textureID, numTileToNextSpawns, tileToNextSpawn;
    fin >> direction;
    mDirection = static_cast<Directions::ID>(direction);

    fin >> mVelocity;

    fin >> numLogs;

    for (int i = 0; i < numLogs; ++i) {
        fin >> textureID;

        Log::Ptr log(createLog(static_cast<Textures::ID>(textureID)));
        mLogs.push_front(log.get());
        mSceneLayers[ObjectLayer]->attachChild(std::move(log));
    }

    fin >> numTileToNextSpawns;

    for (int i = 0; i < numTileToNextSpawns; ++i) {
        fin >> tileToNextSpawn;
        mTileToNextSpawns.push_front(tileToNextSpawn);
    }
}
