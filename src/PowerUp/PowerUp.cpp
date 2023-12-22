#include "PowerUp.hpp"

PowerUp::PowerUp(sf::Time duration, Player& player)
    : mDuration(duration), mPlayer(player) {}

void PowerUp::start() {
    if (mIsActivated || !mCount) {
        return;
    }

    mCount--;
    mIsActivated = true;
    mRemainingDuration = mDuration;
    activate();
}

void PowerUp::update(sf::Time deltaTime) {
    if (!mIsActivated) {
        return;
    }

    mRemainingDuration -= deltaTime;

    if (mRemainingDuration <= sf::Time::Zero) {
        mIsActivated = false;
        deactivate();
    }
}

void PowerUp::increaseCount() { mCount++; }

void PowerUp::deactivate() {}
