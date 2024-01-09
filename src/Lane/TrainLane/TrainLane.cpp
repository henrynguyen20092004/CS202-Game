#include "TrainLane.hpp"

#include "../../FileIO/FileIO.hpp"
#include "../../Global/Global.hpp"
#include "../../Random/Random.hpp"
#include "../../Vehicle/Train/Train.hpp"

TrainLane::TrainLane(
    TextureHolder& textureHolder, int seasonIndex, const sf::Vector2f& position,
    bool isLoading
)
    : Lane(textureHolder, seasonIndex, position) {
    buildScene(isLoading);

    if (isLoading) {
        return;
    }

    mDirection = Random<Directions::ID>::generate(
        {Directions::ID::Left, Directions::ID::Right}
    );
    mVelocity = sf::Vector2f(Random<float>::generate(1000.f, 4000.f), 0.f);
    mSpawnClock = sf::seconds(Random<float>::generate(0.f, 10.f));
}

void TrainLane::handlePlayerCollision(Player& player) {
    if (mTrain) {
        mTrain->handlePlayerCollision(player);
    }
}

void TrainLane::buildScene(bool isLoading) {
    Lane::buildScene(Textures::ID::TrainLane, isLoading);

    for (int i = 0; i < Global::NUM_TILES_X; ++i) {
        SpriteNode::Ptr sprite(new SpriteNode(
            mTextureHolder, Textures::ID::TrainLane,
            sf::IntRect(
                Random<int>::generate({0, 1, 2, 3, 4}, {70, 5, 5, 10, 10}) *
                    Global::TILE_SIZE,
                mSeasonIndex * Global::TILE_SIZE, Global::TILE_SIZE,
                Global::TILE_SIZE
            )
        ));
        sprite->setPosition(i * Global::TILE_SIZE, 0.f);
        mSceneLayers[LaneLayer]->attachChild(std::move(sprite));
    }

    RailwaySignal::Ptr railwaySignal(
        new RailwaySignal(mTextureHolder, mSeasonIndex)
    );
    mRailwaySignal = railwaySignal.get();
    mSceneLayers[SignalLightLayer]->attachChild(std::move(railwaySignal));
}

void TrainLane::addTrain() {
    Vehicle::Ptr train(new Train(mTextureHolder, mSeasonIndex, mDirection));
    train->setVelocity(mVelocity);
    train->setPosition(
        mDirection == Directions::ID::Left ? Global::WINDOW_WIDTH
                                           : -train->getSize().x,
        (Global::TILE_SIZE - train->getSize().y) / 2.f
    );
    mTrain = train.get();
    mSceneLayers[ObjectLayer]->attachChild(std::move(train));
    mSpawnClock = sf::seconds(Random<float>::generate(5.f, 10.f));
}

void TrainLane::removeTrain() {
    mSceneLayers[ObjectLayer]->detachChild(*mTrain);
    mTrain = nullptr;
}

Textures::ID TrainLane::getTextureID() const { return Textures::ID::TrainLane; }

void TrainLane::updateCurrent(sf::Time deltaTime) {
    mSpawnClock -= deltaTime * Global::SPEED_MODIFIER;

    if (mSpawnClock < sf::seconds(1.f)) {
        mRailwaySignal->switchState(RailwaySignal::State::Red);
    }

    if (mSpawnClock < sf::Time::Zero) {
        addTrain();
    }

    if (mTrain) {
        if (mDirection == Directions::ID::Left &&
                mTrain->getPosition().x < -mTrain->getSize().x ||
            mDirection == Directions::ID::Right &&
                mTrain->getPosition().x > Global::WINDOW_WIDTH) {
            removeTrain();
            mRailwaySignal->switchState(RailwaySignal::State::Green);
        }
    }
}

void TrainLane::saveCurrent(std::ofstream& fout) const {
    Lane::saveCurrent(fout);
    fout << static_cast<int>(mDirection) << '\n';
    fout << mVelocity << '\n';
    fout << mSpawnClock << '\n';

    fout << (mTrain != nullptr) << '\n';
}

void TrainLane::loadCurrent(std::ifstream& fin) {
    Lane::loadCurrent(fin);
    int direction;
    fin >> direction;
    mDirection = static_cast<Directions::ID>(direction);

    fin >> mVelocity;
    fin >> mSpawnClock;

    bool hasTrain;
    fin >> hasTrain;

    if (hasTrain) {
        Vehicle::Ptr train(new Train(mTextureHolder, mSeasonIndex, mDirection));
        mTrain = train.get();
        mSceneLayers[ObjectLayer]->attachChild(std::move(train));
    }
}
