#include "World.hpp"

#include "../Global/Global.hpp"
#include "../Score/Score.hpp"

World::World(State::Context context)
    : mWindow(*context.window),
      mTextureHolder(*context.textureHolder),
      mFontHolder(*context.fontHolder),
      mPlayerSettings(*context.playerSettings),
      mPowerUpSettings(*context.powerUpSettings),
      mWorldView(mWindow.getView()) {
    buildScene();
}

void World::handleEvent(const sf::Event& event) {
    mSceneGraph.handleEvent(event);
}

void World::update(sf::Time deltaTime) {
    if (mMap->isPlayerMoved()) {
        mWorldView.move(
            0.f, mScrollSpeed * Global::SPEED_MODIFIER * deltaTime.asSeconds()
        );
    }

    mMap->handlePlayerCollision();
    mSceneGraph.update(deltaTime);
    updateView();
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

    Player::Ptr player(new Player(mTextureHolder, mWorldView, mPlayerSettings));
    mPlayer = player.get();
    mSceneLayers[PlayerLayer]->attachChild(std::move(player));

    Map::Ptr map(new Map(mTextureHolder, mWorldView, mPlayer));
    mMap = map.get();
    mSceneLayers[MapLayer]->attachChild(std::move(map));

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
    float viewY = mWorldView.getCenter().y - mWorldView.getSize().y / 2.f,
          playerY = mPlayer->getWorldPosition().y -
                    (Global::TILE_SIZE - mPlayer->getSize().y) / 2.f;

    if (playerY - Global::NUM_TILES_Y / 2 * Global::TILE_SIZE < viewY) {
        mWorldView.setCenter(
            mWorldView.getCenter().x,
            playerY - Global::NUM_TILES_Y / 2 * Global::TILE_SIZE +
                mWorldView.getSize().y / 2.f
        );
    }
}
