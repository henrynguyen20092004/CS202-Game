#include "World.hpp"

#include "../Animal/Elephant/Elephant.hpp"
#include "../Animal/PolarBear/PolarBear.hpp"
#include "../Global/Global.hpp"
#include "../Score/Score.hpp"

<<<<<<< HEAD
World::World(
    sf::RenderWindow& window, TextureHolder& textureHolder,
    FontHolder& fontHolder
)
    : mWindow(window),
      mWorldView(window.getView()),
      mTextureHolder(textureHolder),
      mFontHolder(fontHolder) {
=======
World::World(State::Context context)
    : mWindow(*context.window),
      mWorldView(mWindow.getView()),
      mTextureHolder(*context.textureHolder),
      mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y),
      mPlayerSettings(*context.playerSettings),
      mPowerUpSettings(*context.powerUpSettings) {
>>>>>>> a7f2657 (Add SettingState)
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
    handlePlayerCollision();
    mSceneGraph.update(deltaTime);
}

void World::draw() {
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

bool World::isPlayerAlive() const { return mPlayer->isAlive(); }

void World::buildScene() {
    for (int i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode);
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }

    Map::Ptr map(new Map(mTextureHolder, mWorldView));
    mMap = map.get();
    mSceneLayers[MapLayer]->attachChild(std::move(map));

    Player::Ptr player(new Player(mTextureHolder, mWorldView, mPlayerSettings));
    mPlayer = player.get();
    mSceneLayers[PlayerLayer]->attachChild(std::move(player));

    PowerUpList::Ptr powerUpList(new PowerUpList(
        mPowerUpSettings, mTextureHolder, mFontHolder, mWorldView, *mPlayer
    ));
    mPowerUpList = powerUpList.get();
    mSceneLayers[IconLayer]->attachChild(std::move(powerUpList));

    // TODO: Remove when adding AnimalFactory
    // PolarBear::Ptr polarBear(
    //     new PolarBear(mTextureHolder, Textures::ID::PolarBear, *mPowerUpList)
    // );
    // mSceneLayers[MapLayer]->attachChild(std::move(polarBear));

    // Elephant::Ptr elephant(
    //     new Elephant(mTextureHolder, Textures::ID::Elephant, *mPowerUpList)
    // );
    // mSceneLayers[MapLayer]->attachChild(std::move(elephant));

    Score::Ptr score(new Score(*mPlayer, mWorldView, mFontHolder));
    mSceneLayers[IconLayer]->attachChild(std::move(score));
}

void World::updateView() {
    float viewY = mWorldView.getCenter().y, playerY = mPlayer->getPosition().y;

    if (playerY < viewY) {
        mWorldView.setCenter(mWorldView.getCenter().x, playerY);
    }
}

void World::handlePlayerCollision() { mMap->handlePlayerCollision(*mPlayer); }
