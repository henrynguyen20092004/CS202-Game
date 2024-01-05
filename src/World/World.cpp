#include "World.hpp"

#include "../FallingSnow/FallingSnow.hpp"
#include "../Global/Global.hpp"
#include "../Score/Score.hpp"

World::World(const State::Context& context, bool isMultiplayer, bool isLoading)
    : mWindow(*context.window),
      mTextureHolder(*context.textureHolder),
      mFontHolder(*context.fontHolder),
      mWorldView(mWindow.getView()),
      mPlayers(1 + isMultiplayer, nullptr),
      mPowerUpLists(1 + isMultiplayer, nullptr) {
    Global::setDefault();
    buildScene(context, isLoading);
}

World::~World() {
    saveWorld();
    savePlayerTexture();
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

int World::getDeadPlayer() const {
    for (int i = 0; i < mPlayers.size(); ++i) {
        if (!mPlayers[i]->isAlive()) {
            return i;
        }
    }

    return -1;
}

void World::buildScene(const State::Context& context, bool isLoading) {
    if (isLoading) {
        loadPlayerTexture();
    }

    for (int i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode);
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }

    Player::Ptr player(new Player(
        mTextureHolder,
        mPlayers.size() == 1 ? Textures::ID::Player1SelectedChoiceSingle
                             : Textures::ID::Player1SelectedChoiceMulti,
        mWorldView, *context.playerSettings1, 0
    ));
    mPlayers[0] = player.get();
    mSceneLayers[PlayerLayer]->attachChild(std::move(player));

    if (mPlayers.size() == 2) {
        player.reset(new Player(
            mTextureHolder, Textures::ID::Player2SelectedChoiceMulti,
            mWorldView, *context.playerSettings2, 1
        ));
        mPlayers[1] = player.get();
        mSceneLayers[PlayerLayer]->attachChild(std::move(player));

        mPlayers[0]->setName(*context.fontHolder);
        mPlayers[1]->setName(*context.fontHolder);
    }

    PowerUpList::Ptr powerUpList(new PowerUpList(
        *context.powerUpSettings1, mTextureHolder, mFontHolder, mWorldView,
        *mPlayers[0]
    ));
    mPowerUpLists[0] = powerUpList.get();
    mSceneLayers[IconLayer]->attachChild(std::move(powerUpList));

    if (mPlayers.size() == 2) {
        powerUpList.reset(new PowerUpList(
            *context.powerUpSettings2, mTextureHolder, mFontHolder, mWorldView,
            *mPlayers[1]
        ));
        mPowerUpLists[1] = powerUpList.get();
        mSceneLayers[IconLayer]->attachChild(std::move(powerUpList));
    }

    FallingSnow::Ptr fallingSnow(new FallingSnow(mWorldView));
    mSceneLayers[EffectLayer]->attachChild(std::move(fallingSnow));

    if (mPlayers.size() == 1) {
        Score::Ptr score(new Score(*mPlayers[0], mWorldView, mFontHolder));
        mScore = score.get();
        mSceneLayers[IconLayer]->attachChild(std::move(score));
    }

    Map::Ptr map(new Map(
        mTextureHolder, mWorldView, mPlayers, mPowerUpLists, mScore, isLoading
    ));
    mMap = map.get();
    mSceneLayers[MapLayer]->attachChild(std::move(map));

    if (isLoading) {
        loadWorld();
    }
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

void World::saveWorld() {
    std::ofstream fout;

    if (mPlayers.size() == 1) {
        fout.open("data/Singleplayer.txt");
        mPlayers[0]->save(fout);
        mPowerUpLists[0]->save(fout);
        mScore->save(fout);
    } else {
        fout.open("data/Multiplayer.txt");
        mPlayers[0]->save(fout);
        mPlayers[1]->save(fout);
        mPowerUpLists[0]->save(fout);
        mPowerUpLists[1]->save(fout);
    }

    mMap->save(fout);
    Global::save(fout);
    fout.close();
}

void World::loadWorld() {
    std::ifstream fin;

    if (mPlayers.size() == 1) {
        fin.open("data/Singleplayer.txt");
        mPlayers[0]->load(fin);
        mPowerUpLists[0]->load(fin);
        mScore->load(fin);
    } else {
        fin.open("data/Multiplayer.txt");
        mPlayers[0]->load(fin);
        mPlayers[1]->load(fin);
        mPowerUpLists[0]->load(fin);
        mPowerUpLists[1]->load(fin);
    }

    mMap->load(fin);
    Global::load(fin);
    fin.close();

    for (int i = 0; i < mPlayers.size(); ++i) {
        mPlayers[i]->setTargetTile(mMap->getPlayerTile(i));
    }
}

void World::savePlayerTexture() const {
    std::ofstream fout("data/PlayerTexture.txt");
    std::vector<Textures::ID> possibleIDs = {
        Textures::ID::PlayerChoice1, Textures::ID::PlayerChoice2,
        Textures::ID::PlayerChoice3, Textures::ID::PlayerChoice4,
        Textures::ID::PlayerChoice5, Textures::ID::PlayerChoice6,
    };

    fout << static_cast<int>(mTextureHolder.getSharedID(
                Textures::ID::Player1SelectedChoiceSingle, possibleIDs
            ))
         << ' '
         << static_cast<int>(mTextureHolder.getSharedID(
                Textures::ID::Player1SelectedChoiceMulti, possibleIDs
            ))
         << ' '
         << static_cast<int>(mTextureHolder.getSharedID(
                Textures::ID::Player2SelectedChoiceMulti, possibleIDs
            ))
         << '\n';
    fout.close();
}

void World::loadPlayerTexture() {
    std::ifstream fin("data/PlayerTexture.txt");
    int textureID;
    fin >> textureID;
    mTextureHolder.load(
        Textures::ID::Player1SelectedChoiceSingle,
        static_cast<Textures::ID>(textureID)
    );
    fin >> textureID;
    mTextureHolder.load(
        Textures::ID::Player1SelectedChoiceMulti,
        static_cast<Textures::ID>(textureID)
    );
    fin >> textureID;
    mTextureHolder.load(
        Textures::ID::Player2SelectedChoiceMulti,
        static_cast<Textures::ID>(textureID)
    );
    fin.close();
}
