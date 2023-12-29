#include "Lane.hpp"

#include "../Global/Global.hpp"

Lane::Lane(TextureHolder& textureHolder, const sf::Vector2f& position)
    : mTextureHolder(textureHolder) {
    setPosition(position);
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

    for (int i = 0; i < Global::NUM_TILES_X; ++i) {
        Tile::Ptr tile(new Tile(
            textureID == Textures::ID::River ? Tile::Type::Bad
                                             : Tile::Type::Good,
            sf::Vector2f(i * Global::TILE_SIZE, 0.f)
        ));
        mLaneTiles.push_back(tile.get());
        mSceneLayers[TileLayer]->attachChild(std::move(tile));
    }
}
