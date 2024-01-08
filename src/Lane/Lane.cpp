#include "Lane.hpp"

#include <limits>

#include "../Global/Global.hpp"
#include "../SpriteNode/SpriteNode.hpp"

Lane::Lane(TextureHolder& textureHolder, const sf::Vector2f& position)
    : mTextureHolder(textureHolder) {
    setPosition(position);
}

Tile* Lane::getTile(int index) const { return mLaneTiles[index]; }

Tile* Lane::getNearestTile(
    Tile* tile, Tile::Type type, Directions::ID direction
) const {
    Tile* nearestTile = nullptr;
    float nearestTileDistance = std::numeric_limits<float>::max();

    for (Tile* laneTile : mLaneTiles) {
        if (laneTile->getType() != type ||
            (direction == Directions::ID::Left &&
             laneTile->getWorldPosition().x >= tile->getWorldPosition().x) ||
            (direction == Directions::ID::Right &&
             laneTile->getWorldPosition().x <= tile->getWorldPosition().x)) {
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

Tile* Lane::getPlayerTile(float playerWorldPosX) const {
    for (Tile* laneTile : mLaneTiles) {
        if (laneTile->getWorldPosition().x < playerWorldPosX &&
            laneTile->getWorldPosition().x + Global::TILE_SIZE >
                playerWorldPosX) {
            return laneTile;
        }
    }

    return nullptr;
}

void Lane::handlePlayerCollision(Player& player) {}

void Lane::buildScene(Textures::ID textureID, bool isLoading) {
    for (int i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode);
        mSceneLayers[i] = layer.get();
        attachChild(std::move(layer));
    }

    if (textureID == Textures::ID::RiverLane) {
        return;
    }

    for (int i = -1; i <= Global::NUM_TILES_X; ++i) {
        Tile::Ptr tile(
            new Tile(Tile::Type::Good, sf::Vector2f(i * Global::TILE_SIZE, 0.f))
        );
        mLaneTiles.push_back(tile.get());
        mSceneLayers[TileLayer]->attachChild(std::move(tile));
    }
}

void Lane::saveCurrent(std::ofstream& fout) const {
    SceneNode::saveCurrent(fout);
    fout << static_cast<int>(mLaneTiles.size()) << '\n';
}

void Lane::loadCurrent(std::ifstream& fin) {
    SceneNode::loadCurrent(fin);
    int numTiles;
    fin >> numTiles;

    if (getTextureID() != Textures::ID::RiverLane) {
        return;
    }

    for (int i = 0; i < numTiles; ++i) {
        Tile::Ptr tile(new Tile(Tile::Type::None, sf::Vector2f()));
        mLaneTiles.push_back(tile.get());
        mSceneLayers[TileLayer]->attachChild(std::move(tile));
    }
}
