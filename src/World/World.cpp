#include "World.hpp"

#include "../Global/Global.hpp"
#include "../Lane/VehicleLane/VehicleLane.hpp"
#include "../Player/Player.hpp"

World::World(sf::RenderWindow& window, TextureHolder& textures)
    : mWindow(window),
      mTextureHolder(textures),
      mWorldView(window.getView()),
      mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y) {
    mWorldView.setCenter(
        mWorldView.getCenter().x, mWorldBounds.height - mWorldView.getCenter().y
    );

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

    for (int i = 0; i < 9; i++) {
        Lane::Ptr lane(new VehicleLane(
            mTextureHolder, sf::Vector2f(0.f, i * Global::TILE_SIZE)
        ));
        mSceneLayers[Lane]->attachChild(std::move(lane));
    }

    std::unique_ptr<Player> player(new Player(mTextureHolder, mWorldView));
    mSceneLayers[Ground]->attachChild(std::move(player));
}
