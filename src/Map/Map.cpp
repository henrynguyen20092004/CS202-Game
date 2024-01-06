#include "Map.hpp"

#include "../Global/Global.hpp"
#include "../Lane/ObstacleLane/ObstacleLane.hpp"
#include "../Lane/RiverLane/RiverLane.hpp"
#include "../Lane/TrainLane/TrainLane.hpp"
#include "../Lane/VehicleLane/VehicleLane.hpp"
#include "../Random/Random.hpp"

Map::Map(
    TextureHolder& textureHolder, sf::View& worldView,
    const std::vector<Player*>& players,
    const std::vector<PowerUpList*>& powerUpList, Score* score, bool isLoading
)
    : mTextureHolder(textureHolder),
      mWorldView(worldView),
      mPlayers(players),
      mPowerUpList(powerUpList),
      mScore(score) {
    if (isLoading) {
        return;
    }

    initLanes();
    initPlayer();

    if (mScore) {
        mScore->init();
    }
}

bool Map::isPlayerMoved() const { return mIsPlayerMoved; }

void Map::handlePlayerCollision() {
    if (mPlayers.size() == 2) {
        mPlayers[0]->handlePlayerCollision(*mPlayers[1]);
        mPlayers[1]->handlePlayerCollision(*mPlayers[0]);
    }

    for (Lane* lane : mLanes) {
        for (Player* player : mPlayers) {
            lane->handlePlayerCollision(*player);
        }
    }
}

Tile* Map::getPlayerTile(int playerIndex) const {
    return mLanes[getPlayerLaneIndex(playerIndex)]->getPlayerTile(
        mPlayers[playerIndex]->getWorldPosition().x
    );
}

void Map::initPlayer() {
    for (int i = 0; i < mPlayers.size(); ++i) {
        Tile* playerTile = mLanes[Global::NUM_TILES_Y - 2]->getTile(
            Global::NUM_TILES_X / 2 + i
        );
        mPlayers[i]->setPosition(
            playerTile->getWorldPosition() +
            (sf::Vector2f(Global::TILE_SIZE, Global::TILE_SIZE) -
             mPlayers[i]->getSize()) /
                2.f
        );
        mPlayers[i]->setTargetTile(playerTile);
    }
}

int Map::getPlayerLaneIndex(int playerIndex) const {
    for (int i = 0; i < mLanes.size() - 1; ++i) {
        if (mLanes[i]->getPosition().y <
                mPlayers[playerIndex]->getWorldPosition().y &&
            mLanes[i + 1]->getPosition().y >
                mPlayers[playerIndex]->getWorldPosition().y) {
            return i;
        }
    }

    mPlayers[playerIndex]->kill();
    return -1;
}

Tile* Map::getPlayerNextTile(int playerIndex, Directions::ID direction) const {
    assert(direction != Directions::ID::None);

    int playerLaneIndex = getPlayerLaneIndex(playerIndex);
    Tile* playerNextTile = nullptr;

    for (Tile::Type type : {Tile::Type::Good, Tile::Type::Bad}) {
        playerNextTile =
            mLanes
                [playerLaneIndex - (direction == Directions::ID::Up) +
                 (direction == Directions::ID::Down)]
                    ->getNearestTile(
                        mPlayers[playerIndex]->getSourceTile(), type,
                        (direction == Directions::ID::Left ||
                         direction == Directions::ID::Right)
                            ? direction
                            : Directions::ID::None
                    );

        if (playerNextTile &&
            mPlayers[playerIndex]->getSourceTile()->distanceTo(playerNextTile
            ) <= 101.f) {
            break;
        }
    }

    if (!playerNextTile) {
        mPlayers[playerIndex]->kill();
    }

    return playerNextTile;
}

void Map::movePlayerTile(int playerIndex, Tile* destinationTile) {
    if (!destinationTile) {
        mPlayers[playerIndex]->kill();
        return;
    }

    mPlayers[playerIndex]->setTargetTile(destinationTile);
}

Lane* Map::createLane(
    Textures::ID textureID, sf::Vector2f position, bool isLoading
) {
    switch (textureID) {
        case Textures::ID::VehicleLane:
            return new VehicleLane(mTextureHolder, position, isLoading);

        case Textures::ID::TrainLane:
            return new TrainLane(mTextureHolder, position, isLoading);

        case Textures::ID::ObstacleLane:
            return new ObstacleLane(
                mTextureHolder, position, mPowerUpList, mScore, isLoading
            );

        case Textures::ID::RiverLane:
            return new RiverLane(mTextureHolder, position, isLoading);

        default:
            return nullptr;
    }
}

void Map::initLanes() {
    for (int i = -1; i < Global::NUM_TILES_Y; ++i) {
        if (i <= 2) {
            addEmptyLane();
        } else {
            addRandomLane();
        }
    }
}

void Map::addEmptyLane() {
    Lane::Ptr lane(new ObstacleLane(
        mTextureHolder,
        sf::Vector2f(
            0, (mLanes.empty() ? Global::WINDOW_HEIGHT + Global::TILE_SIZE
                               : mLanes.front()->getPosition().y) -
                   Global::TILE_SIZE
        ),
        mPowerUpList, mScore, false, true
    ));
    mLanes.push_front(lane.get());
    attachChild(std::move(lane));
}

void Map::addRandomLane() {
    Lane::Ptr lane(createLane(
        Random<Textures::ID>::generate(
            {Textures::ID::VehicleLane, Textures::ID::TrainLane,
             Textures::ID::ObstacleLane, Textures::ID::RiverLane},
            {30, 20, 30, 20}
        ),
        sf::Vector2f(
            0, (mLanes.empty() ? Global::WINDOW_HEIGHT
                               : mLanes.front()->getPosition().y) -
                   Global::TILE_SIZE
        ),
        false
    ));
    mLanes.push_front(lane.get());
    attachChild(std::move(lane));
}

void Map::removeLane() {
    detachChild(*mLanes.back());
    mLanes.pop_back();
}

void Map::updateLanes() {
    if (mLanes.front()->getPosition().y > mWorldView.getCenter().y -
                                              mWorldView.getSize().y / 2.f -
                                              Global::TILE_SIZE) {
        addRandomLane();
        Global::DIFFICULTY_MODIFIER += 0.01f;
    }

    if (mLanes.back()->getPosition().y > mWorldView.getCenter().y +
                                             mWorldView.getSize().y / 2.f +
                                             Global::TILE_SIZE) {
        removeLane();
    }
}

void Map::updatePlayer() {
    for (int i = 0; i < mPlayers.size(); ++i) {
        if (!mPlayers[i]->askToMove()) {
            continue;
        }

        Directions::ID direction = mPlayers[i]->getDirection();

        if (direction == Directions::ID::None) {
            return;
        }

        mIsPlayerMoved = true;
        movePlayerTile(i, getPlayerNextTile(i, direction));
    }
}

void Map::updateCurrent(sf::Time deltaTime) {
    updateLanes();
    updatePlayer();
}

void Map::saveCurrent(std::ofstream& fout) const {
    SceneNode::saveCurrent(fout);
    int numLanes = mLanes.size();
    fout << numLanes << '\n';

    for (int i = numLanes - 1; i >= 0; --i) {
        fout << static_cast<int>(mLanes[i]->getTextureID()) << (i ? ' ' : '\n');
    }

    fout << mIsPlayerMoved << '\n';
}

void Map::loadCurrent(std::ifstream& fin) {
    SceneNode::loadCurrent(fin);
    int numLanes, textureID;
    fin >> numLanes;

    for (int i = 0; i < numLanes; ++i) {
        fin >> textureID;

        Lane::Ptr lane(createLane(
            static_cast<Textures::ID>(textureID), sf::Vector2f(), true
        ));
        mLanes.push_front(lane.get());
        attachChild(std::move(lane));
    }

    fin >> mIsPlayerMoved;
}
