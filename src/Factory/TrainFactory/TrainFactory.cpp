#include "TrainFactory.hpp"

#include "../../Global/Global.hpp"
#include "../../Random/Random.hpp"

TrainFactory::TrainFactory(TextureHolder& textureHolder)
    : Factory(textureHolder), mTrain(nullptr) {
    mDirection = Random<Directions::ID>::generate(
        {Directions::ID::Left, Directions::ID::Right}
    );

    if (mDirection == Directions::ID::Left) {
        mTextureID = Textures::ID::TrainLeft;
    } else {
        mTextureID = Textures::ID::TrainRight;
    }

    mVelocity = sf::Vector2f(Random<float>::generate(5000.f, 10000.f), 0.f);

    mSpawnClock = sf::Time(sf::seconds(Random<float>::generate(0.f, 10.f)));
}

void TrainFactory::addTrain() {
    Vehicle::Ptr train(new Vehicle(mTextureHolder, mTextureID, mDirection));
    train->setVelocity(mVelocity);
    if (mDirection == Directions::ID::Left) {
        train->setPosition(
            Global::WINDOW_WIDTH, (Global::TILE_SIZE - train->getSize().y) / 2.f
        );
    } else {
        train->setPosition(
            -train->getSize().x, (Global::TILE_SIZE - train->getSize().y) / 2.f
        );
    }

    mTrain = train.get();
    attachChild(std::move(train));
}

void TrainFactory::removeTrain() {
    detachChild(*mTrain);
    mTrain = nullptr;
}

void TrainFactory::updateCurrent(sf::Time deltaTime) {
    mSpawnClock -= deltaTime;

    if (mSpawnClock < sf::Time::Zero) {
        addTrain();

        mSpawnClock = sf::Time(sf::seconds(Random<float>::generate(5.f, 10.f)));
    }

    if (mTrain != nullptr) {
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
