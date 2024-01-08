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

    mVelocity = sf::Vector2f(Random<float>::generate(250.f, 300.f), 0.f);

    init();
}

void River::buildScene() {
    Lane::buildScene(Textures::ID::River);

    for (int i = 0; i < Global::NUM_TILES_X; ++i) {
        SpriteNode::Ptr sprite(new SpriteNode(
            mTextureHolder, Textures::ID::River,
            sf::IntRect(
                Random<int>::generate({0, 1, 2, 3}, {90, 0, 5, 5}) *
                    Global::TILE_SIZE,
                0, Global::TILE_SIZE, Global::TILE_SIZE
            )
        ));
        sprite->setPosition(i * Global::TILE_SIZE, 0.f);
        mSceneLayers[LaneLayer]->attachChild(std::move(sprite));
    }
}

void River::init() {
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
    mTileToNextSpawns.push_front(Random<int>::generate(1, 5));

    addLogTiles(position);
}

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

void River::addLogTiles(const sf::Vector2f& logPosition) {
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
            Tile::Type::Bad,
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

void River::addLog() {
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

    float backLogPosX = mLogs.back()->getPosition().x;

    if (mDirection == Directions::ID::Left &&
            backLogPosX < -mLogs.back()->getSize().x - Global::TILE_SIZE ||
        mDirection == Directions::ID::Right &&
            backLogPosX > Global::WINDOW_WIDTH + Global::TILE_SIZE) {
        removeLog();
    }
}
