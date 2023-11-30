#include "World.hpp"

#include "../Player/Player.hpp"

World::World(sf::RenderWindow& window, TextureHolder& textures)
    : mWindow(window),
      mTextures(textures),
      mWorldView(window.getView()),
      mWorldBounds(
          0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y * 3
      ) {
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

    // TODO: Remove when adding TileMap
    sf::Texture& texture = mTextures.get(Textures::ID::Background);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

    std::unique_ptr<SpriteNode> backgroundSprite(
        new SpriteNode(texture, textureRect)
    );
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

    std::unique_ptr<Player> player(
        new Player(mTextures.get(Textures::ID::Player), mWorldView)
    );
    mSceneLayers[Ground]->attachChild(std::move(player));
}
