#include "TrainLane.hpp"

#include "../../Global/Global.hpp"
#include "../../Random/Random.hpp"
#include "../../Vehicle/Train/Train.hpp"

TrainLane::TrainLane(TextureHolder& textureHolder, const sf::Vector2f& position)
    : Lane(textureHolder, position), mTrain(nullptr) {
    buildScene();

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

void TrainLane::buildScene() {
    Lane::buildScene(Textures::ID::TrainLane);

    for (int i = 0; i < Global::NUM_TILES_X; ++i) {
        SpriteNode::Ptr sprite(new SpriteNode(
            mTextureHolder, Textures::ID::TrainLane,
            sf::IntRect(
                Random<int>::generate({0}) * Global::TILE_SIZE, 0,
                Global::TILE_SIZE, Global::TILE_SIZE
            )
        ));
        sprite->setPosition(i * Global::TILE_SIZE, 0.f);
        mSceneLayers[LaneLayer]->attachChild(std::move(sprite));
    }

    RailwaySignal::Ptr railwaySignal(new RailwaySignal(mTextureHolder));
    mRailwaySignal = railwaySignal.get();
    mSceneLayers[SignalLightLayer]->attachChild(std::move(railwaySignal));
}

void TrainLane::addTrain() {
    Vehicle::Ptr train(new Train(mTextureHolder, mDirection));
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
