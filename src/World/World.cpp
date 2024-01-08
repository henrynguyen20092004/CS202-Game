#include "World.hpp"

#include "../Global/Global.hpp"
#include "../Score/Score.hpp"

World::World(const State::Context& context, bool isMultiplayer)
    : mWindow(*context.window),
      mTextureHolder(*context.textureHolder),
      mFontHolder(*context.fontHolder),
      mWorldView(mWindow.getView()),
      mPlayers(1 + isMultiplayer, nullptr) {
    Global::SPEED_MODIFIER = 1.f;
    Global::DIFFICULTY_MODIFIER = 1.f;
    buildScene(context);
}

void World::handleEvent(const sf::Event& event) {
    mSceneGraph.handleEvent(event);
}

void World::update(sf::Time deltaTime) {
    if (mMap->isPlayerMoved()) {
        mWorldView.move(
            0.f, mScrollSpeed * Global::SPEED_MODIFIER *
                     Global::DIFFICULTY_MODIFIER * deltaTime.asSeconds()
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

bool World::isPlayerAlive() const {
    for (Player* player : mPlayers) {
        if (!player->isAlive()) {
            return false;
        }
    }

    return true;
}

void World::buildScene(const State::Context& context) {
    for (int i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode);
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }

    Player::Ptr player(new Player(
        mTextureHolder, Textures::ID::Player1SelectedChoice, mWorldView,
        *context.playerSettings1, 0
    ));
    mPlayers[0] = player.get();
    mSceneLayers[PlayerLayer]->attachChild(std::move(player));

    if (mPlayers.size() == 2) {
        player.reset(new Player(
            mTextureHolder, Textures::ID::Player2SelectedChoice, mWorldView,
            *context.playerSettings2, 1
        ));
        mPlayers[1] = player.get();
        mSceneLayers[PlayerLayer]->attachChild(std::move(player));

        mPlayers[0]->setName(*context.fontHolder);
        mPlayers[1]->setName(*context.fontHolder);
    }

    std::vector<PowerUpList*> powerUpLists;
    PowerUpList::Ptr powerUpList(new PowerUpList(
        *context.powerUpSettings1, mTextureHolder, mFontHolder, mWorldView,
        *mPlayers[0]
    ));
    powerUpLists.push_back(powerUpList.get());
    mSceneLayers[IconLayer]->attachChild(std::move(powerUpList));

    if (mPlayers.size() == 2) {
        powerUpList.reset(new PowerUpList(
            *context.powerUpSettings2, mTextureHolder, mFontHolder, mWorldView,
            *mPlayers[1]
        ));
        powerUpLists.push_back(powerUpList.get());
        mSceneLayers[IconLayer]->attachChild(std::move(powerUpList));
    }

    Score* scorePointer = nullptr;
    if (mPlayers.size() == 1) {
        Score::Ptr score(new Score(*mPlayers[0], mWorldView, mFontHolder));
        scorePointer = score.get();
        mSceneLayers[IconLayer]->attachChild(std::move(score));
    }

    Map::Ptr map(new Map(
        mTextureHolder, mWorldView, mPlayers, powerUpLists, scorePointer
    ));
    mMap = map.get();
    mSceneLayers[MapLayer]->attachChild(std::move(map));
}

void World::updateView() {
    float viewY = mWorldView.getCenter().y - mWorldView.getSize().y / 2.f,
          playerY = Global::WINDOW_HEIGHT;

    for (int i = 0; i < mPlayers.size(); ++i) {
        playerY = std::min(
            playerY, mPlayers[i]->getWorldPosition().y -
                         (Global::TILE_SIZE - mPlayers[i]->getSize().y) / 2.f
        );
    }

    if (playerY - Global::NUM_TILES_Y / 2 * Global::TILE_SIZE < viewY) {
        mWorldView.setCenter(
            mWorldView.getCenter().x,
            playerY - Global::NUM_TILES_Y / 2 * Global::TILE_SIZE +
                mWorldView.getSize().y / 2.f
        );
    }
}
