#include "World.hpp"

#include "../Global/Global.hpp"
#include "../Lane/VehicleLane/VehicleLane.hpp"
#include "../Map/Map.hpp"

World::World(sf::RenderWindow& window, TextureHolder& textureHolder)
    : mWindow(window),
      mWorldView(window.getView()),
      mTextureHolder(textureHolder),
      mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y) {
    buildScene();
}

void World::handleEvent(const sf::Event& event) {
    mSceneGraph.handleEvent(event);
}

void World::update(sf::Time deltaTime) {
    mWorldView.move(0.f, mScrollSpeed * deltaTime.asSeconds());
    updateView();
    mSceneGraph.update(deltaTime);
}

void World::draw() {
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

void World::buildScene() {
    for (int i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }

    Map::Ptr map(new Map(mTextureHolder, mWorldView));
    mSceneLayers[MapLayer]->attachChild(std::move(map));

    std::unique_ptr<Player> player(
        new Player(mTextureHolder, mWorldView, mPlayerSettings)
    );
    mPlayer = player.get();
    mSceneLayers[PlayerLayer]->attachChild(std::move(player));
}

void World::updateView() {
    float viewY = mWorldView.getCenter().y, playerY = mPlayer->getPosition().y;

    if (playerY < viewY) {
        mWorldView.setCenter(mWorldView.getCenter().x, playerY);
    }
}
