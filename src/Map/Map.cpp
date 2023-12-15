#include "Map.hpp"

#include "../Global/Global.hpp"
#include "../Lane/TrainLane/TrainLane.hpp"
#include "../Lane/VehicleLane/VehicleLane.hpp"
#include "../Random/Random.hpp"

Map::Map(TextureHolder& textureHolder, sf::View& worldView)
    : mTextureHolder(textureHolder), mWorldView(worldView) {
    for (int i = 0; i < Global::WINDOW_HEIGHT / Global::TILE_SIZE; ++i) {
        addLane();
    }
}

void Map::addLane() {
    Textures::ID textureID = Random<Textures::ID>::generate(
        {Textures::ID::VehicleLane, Textures::ID::TrainLane}
    );

    Lane::Ptr lane;
    sf::Vector2f position = sf::Vector2f(
        0, (mLanes.empty() ? Global::WINDOW_HEIGHT
                           : mLanes.front()->getPosition().y) -
               Global::TILE_SIZE
    );
    switch (textureID) {
        case Textures::ID::VehicleLane:
            lane = std::make_unique<VehicleLane>(mTextureHolder, position);
            break;

        case Textures::ID::TrainLane:
            lane = std::make_unique<TrainLane>(mTextureHolder, position);
            break;

        default:
            break;
    }

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
        addLane();
    }

    if (mLanes.back()->getPosition().y >
        mWorldView.getCenter().y + mWorldView.getSize().y / 2.f) {
        removeLane();
    }
}
