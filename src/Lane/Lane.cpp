#include "Lane.hpp"

#include <cassert>
#include <limits>

#include "../Global/Global.hpp"
#include "../SpriteNode/SpriteNode.hpp"

Lane::Lane(TextureHolder& textureHolder, const sf::Vector2f& position)
    : mTextureHolder(textureHolder) {
    setPosition(position);
}

Tile* Lane::getTile(int index) const {
    assert(index >= 0 && index < Global::NUM_TILES_X);
    return mLaneTiles[index];
}

Tile* Lane::getNearestTile(
    Tile* tile, Tile::Type type, Directions::ID direction
) const {
    assert(
        direction == Directions::ID::Left ||
        direction == Directions::ID::Right || direction == Directions::ID::None
    );

    Tile* nearestTile = nullptr;
    float nearestTileDistance = std::numeric_limits<float>::max();

    for (auto& laneTile : mLaneTiles) {
        if (laneTile->getType() != type ||
            (direction == Directions::ID::Left &&
             laneTile->getGlobalPosition().x >= tile->getGlobalPosition().x) ||
            (direction == Directions::ID::Right &&
             laneTile->getGlobalPosition().x <= tile->getGlobalPosition().x)) {
            continue;
        }

        float distance = tile->distanceTo(laneTile);

        if (distance < nearestTileDistance) {
            nearestTile = laneTile;
            nearestTileDistance = distance;
        }
    }

    return nearestTile;
}

void Lane::handlePlayerCollision(Player& player) {}

void Lane::buildScene(Textures::ID textureID) {
    for (int i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode);
        mSceneLayers[i] = layer.get();
        attachChild(std::move(layer));
    }

    SpriteNode::Ptr sprite(new SpriteNode(mTextureHolder, textureID));
    mSceneLayers[LaneLayer]->attachChild(std::move(sprite));

    if (textureID == Textures::ID::River) {
        return;
    }

    for (int i = 0; i < Global::NUM_TILES_X; ++i) {
        Tile::Ptr tile(
            new Tile(Tile::Type::Good, sf::Vector2f(i * Global::TILE_SIZE, 0.f))
        );
        mLaneTiles.push_back(tile.get());
        mSceneLayers[TileLayer]->attachChild(std::move(tile));
    }
}
