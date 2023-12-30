#include "Map.hpp"

#include "../Global/Global.hpp"
#include "../Lane/ObstacleLane/ObstacleLane.hpp"
#include "../Lane/River/River.hpp"
#include "../Lane/TrainLane/TrainLane.hpp"
#include "../Lane/VehicleLane/VehicleLane.hpp"
#include "../Random/Random.hpp"

Map::Map(TextureHolder& textureHolder, sf::View& worldView, Player* player)
    : mTextureHolder(textureHolder), mWorldView(worldView), mPlayer(player) {
    initLanes();
    initPlayer();
}

void Map::handlePlayerCollision() {
    for (Lane* lane : mLanes) {
        lane->handlePlayerCollision(*mPlayer);
    }
}

void Map::initPlayer() {
    Tile* playerTile =
        mLanes[Global::NUM_TILES_Y - 2]->getTile(Global::NUM_TILES_X / 2);
    mPlayer->setPosition(
        playerTile->getGlobalPosition() +
        (sf::Vector2f(Global::TILE_SIZE, Global::TILE_SIZE) - mPlayer->getSize()
        ) / 2.f
    );
    mPlayer->setTargetTile(playerTile);
}

int Map::getPlayerLaneIndex() const {
    for (int i = 0; i < mLanes.size() - 1; ++i) {
        if (mLanes[i]->getPosition().y <
                mPlayer->getGlobalBounds().getPosition().y &&
            mLanes[i + 1]->getPosition().y >
                mPlayer->getGlobalBounds().getPosition().y) {
            return i;
        }
    }

    mPlayer->kill();
    return -1;
}

Tile* Map::getPlayerNextTile(Directions::ID direction) const {
    assert(direction != Directions::ID::None);

    int playerLaneIndex = getPlayerLaneIndex();
    Tile* playerNextTile = nullptr;
    for (auto type : {Tile::Type::Good, Tile::Type::Bad}) {
        playerNextTile =
            mLanes
                [playerLaneIndex - (direction == Directions::ID::Up) +
                 (direction == Directions::ID::Down)]
                    ->getNearestTile(
                        mPlayer->getSourceTile(), type,
                        (direction == Directions::ID::Left ||
                         direction == Directions::ID::Right)
                            ? direction
                            : Directions::ID::None
                    );  // Good luck understanding this

        if (playerNextTile != nullptr) {
            break;
        }
    }

    if (playerNextTile == nullptr) {
        mPlayer->kill();
    }

    return playerNextTile;
}

void Map::movePlayerTile(Tile* destinationTile) {
    if (!destinationTile) {
        mPlayer->kill();
        return;
    }

    mPlayer->setTargetTile(destinationTile);
}

void Map::addEmptyLane() {
    Lane::Ptr lane(new ObstacleLane(
        mTextureHolder,
        sf::Vector2f(
            0, (mLanes.empty() ? Global::WINDOW_HEIGHT
                               : mLanes.front()->getPosition().y) -
                   Global::TILE_SIZE
        ),
        true
    ));

    mLanes.push_front(lane.get());
    attachChild(std::move(lane));
}

Lane* Map::makeLane(Textures::ID textureID, sf::Vector2f position) {
    switch (textureID) {
        case Textures::ID::VehicleLane:
            return new VehicleLane(mTextureHolder, position);

        case Textures::ID::TrainLane:
            return new TrainLane(mTextureHolder, position);

        case Textures::ID::ObstacleLane:
            return new ObstacleLane(mTextureHolder, position);

        case Textures::ID::River:
            return new River(mTextureHolder, position);

        default:
            return nullptr;
    }
}

void Map::initLanes() {
    for (int i = 0; i < Global::NUM_TILES_Y; ++i) {
        if (i <= 2) {
            addEmptyLane();
        } else {
            addRandomLane();
        }
    }
}

void Map::addRandomLane() {
    Lane::Ptr lane(makeLane(
        Random<Textures::ID>::generate(
            {Textures::ID::VehicleLane, Textures::ID::TrainLane,
             Textures::ID::ObstacleLane}
        ),
        sf::Vector2f(
            0, (mLanes.empty() ? Global::WINDOW_HEIGHT
                               : mLanes.front()->getPosition().y) -
                   Global::TILE_SIZE
        )
    ));

    mLanes.push_front(lane.get());
    attachChild(std::move(lane));
}

void Map::removeLane() {
    detachChild(*mLanes.back());
    mLanes.pop_back();
}

void Map::updateLanes() {
    if (mLanes.front()->getPosition().y >
        mWorldView.getCenter().y - mWorldView.getSize().y / 2.f) {
        addRandomLane();
    }

    if (mLanes.back()->getPosition().y > mWorldView.getCenter().y +
                                             mWorldView.getSize().y / 2.f +
                                             Global::TILE_SIZE) {
        removeLane();
    }
}

void Map::updatePlayer() {
    Directions::ID direction = mPlayer->getDirection();
    if (direction == Directions::ID::None) {
        return;
    }

    movePlayerTile(getPlayerNextTile(direction));
    mPlayer->unsetDirection();
}

void Map::updateCurrent(sf::Time deltaTime) {
    updateLanes();
    updatePlayer();
}
