#include "World.hpp"

#include "../Animal/PolarBear/PolarBear.hpp"
#include "../Global/Global.hpp"
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
    mWorldView.move(
        0.f, mScrollSpeed * Global::SPEED_MODIFIER * deltaTime.asSeconds()
    );
    updateView();
    handleCollision();
    mSceneGraph.update(deltaTime);
}

void World::draw() {
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

bool World::isPlayerAlive() const { return mPlayer->isAlive(); }

void World::buildScene() {
    for (int i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }

    Map::Ptr map(new Map(mTextureHolder, mWorldView));
    mSceneLayers[MapLayer]->attachChild(std::move(map));

    Player::Ptr player(new Player(mTextureHolder, mWorldView, mPlayerSettings));
    mPlayer = player.get();
    mSceneLayers[PlayerLayer]->attachChild(std::move(player));

    PowerUpList::Ptr powerUpList(new PowerUpList(*mPlayer, mPowerUpSettings));
    mPowerUpList = powerUpList.get();
    mSceneLayers[PlayerLayer]->attachChild(std::move(powerUpList));

    PolarBear::Ptr polarBear(new PolarBear(
        mTextureHolder, Textures::ID::PolarBear, mWorldView, *mPowerUpList
    ));
    mSceneLayers[MapLayer]->attachChild(std::move(polarBear));
}

void World::handleCollision() {
    std::set<SceneNode::Pair> collisionPairs;
    mSceneGraph.checkNodeCollision(*mPlayer, collisionPairs);

    for (SceneNode::Pair pair : collisionPairs) {
        if (SpriteNode* spriteNode = dynamic_cast<SpriteNode*>(pair.first)) {
            spriteNode->onPlayerCollision(*mPlayer);
        }
    }
}

void World::updateView() {
    float viewY = mWorldView.getCenter().y, playerY = mPlayer->getPosition().y;

    if (playerY < viewY) {
        mWorldView.setCenter(mWorldView.getCenter().x, playerY);
    }
}
