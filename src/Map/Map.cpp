#include "Map.hpp"

#include "../Global/Global.hpp"
#include "../Lane/ObstacleLane/ObstacleLane.hpp"
#include "../Lane/River/River.hpp"
#include "../Lane/TrainLane/TrainLane.hpp"
#include "../Lane/VehicleLane/VehicleLane.hpp"
#include "../Random/Random.hpp"

Map::Map(TextureHolder& textureHolder, sf::View& worldView)
    : mTextureHolder(textureHolder), mWorldView(worldView) {
    for (int i = 0; i < Global::WINDOW_HEIGHT / Global::TILE_SIZE; ++i) {
        if (i <= 2) {
            addEmptyLane();
        } else {
            addRandomLane();
        }
    }
}

void Map::handlePlayerCollision(Player& player) {
    for (Lane* lane : mLanes) {
        lane->handlePlayerCollision(player);
    }
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

void Map::addRandomLane() {
    Lane::Ptr lane(makeLane(
        Random<Textures::ID>::generate(
            {Textures::ID::VehicleLane, Textures::ID::TrainLane,
             Textures::ID::ObstacleLane, Textures::ID::River}
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

void Map::updateCurrent(sf::Time deltaTime) {
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
