#include "World.hpp"

#include "../SpriteNode/SpriteNode.hpp"

World::World(sf::RenderWindow& window)
    : mWindow(window),
      mWorldView(window.getView()),
      mWorldBounds(
          0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y * 3
      ) {
    mWorldView.setCenter(
        mWorldView.getCenter().x, mWorldBounds.height - mWorldView.getCenter().y
    );

    loadTextures();
    buildScene();
}

void World::handleEvent(sf::Event& event) { mSceneGraph.handleEvent(event); }

void World::update(sf::Time deltaTime) {
    mWorldView.move(0.f, mScrollSpeed * deltaTime.asSeconds());
    mSceneGraph.update(deltaTime);
}

void World::draw() {
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

void World::loadTextures() {
    mTextures.load(Textures::ID::Player, "assets/Textures/Player.png");
    mTextures.load(Textures::ID::Background, "assets/Textures/Background.png");
}

void World::buildScene() {
    for (int i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }

    // TODO: Remove when adding TileMap
    sf::Texture& texture = mTextures.get(Textures::ID::Background);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

    std::unique_ptr<SpriteNode> backgroundSprite(
        new SpriteNode(texture, textureRect)
    );
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
}
