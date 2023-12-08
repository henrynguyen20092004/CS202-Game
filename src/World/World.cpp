#include "World.hpp"

#include "../Global/Global.hpp"
#include "../Lane/VehicleLane/VehicleLane.hpp"
#include "../Map/Map.hpp"
#include "../Player/Player.hpp"

World::World(sf::RenderWindow& window, TextureHolder& textures)
    : mWindow(window),
      mTextureHolder(textures),
      mWorldView(window.getView()),
      mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y) {
    buildScene();
}

void World::handleEvent(const sf::Event& event) {
    mSceneGraph.handleEvent(event);
}

void World::update(sf::Time deltaTime) {
    mWorldView.move(0.f, mScrollSpeed * deltaTime.asSeconds());
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

    std::unique_ptr<Player> player(new Player(mTextureHolder, mWorldView));
    mSceneLayers[PlayerLayer]->attachChild(std::move(player));
}
