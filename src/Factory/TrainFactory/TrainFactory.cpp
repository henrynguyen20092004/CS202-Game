#include "TrainFactory.hpp"

#include "../../Global/Global.hpp"
#include "../../Random/Random.hpp"
#include "../../Vehicle/Train/Train.hpp"

TrainFactory::TrainFactory(TextureHolder& textureHolder)
    : Factory(textureHolder), mTrain(nullptr) {
    mDirection = Random<Directions::ID>::generate(
        {Directions::ID::Left, Directions::ID::Right}
    );

    mVelocity = sf::Vector2f(Random<float>::generate(5000.f, 10000.f), 0.f);
    mSpawnClock = sf::seconds(Random<float>::generate(0.f, 10.f));
}

void TrainFactory::handlePlayerCollision(Player& player) {
    if (mTrain) {
        mTrain->handlePlayerCollision(player);
    }
}

void TrainFactory::addTrain() {
    Vehicle::Ptr train(new Train(mTextureHolder, mDirection));
    train->setVelocity(mVelocity);
    train->setPosition(
        mDirection == Directions::ID::Left ? Global::WINDOW_WIDTH
                                           : -train->getSize().x,
        (Global::TILE_SIZE - train->getSize().y) / 2.f
    );
    mTrain = train.get();
    attachChild(std::move(train));
}

void TrainFactory::removeTrain() {
    detachChild(*mTrain);
    mTrain = nullptr;
}

void TrainFactory::updateCurrent(sf::Time deltaTime) {
    mSpawnClock -= deltaTime * Global::SPEED_MODIFIER;

    if (mSpawnClock < sf::Time::Zero) {
        addTrain();
        mSpawnClock = sf::seconds(Random<float>::generate(5.f, 10.f));
    }

    if (mTrain) {
        if (mDirection == Directions::ID::Left) {
            if (mTrain->getPosition().x < -mTrain->getSize().x) {
                removeTrain();
            }
        } else {
            if (mTrain->getPosition().x > Global::WINDOW_WIDTH) {
                removeTrain();
            }
        }
    }
}
