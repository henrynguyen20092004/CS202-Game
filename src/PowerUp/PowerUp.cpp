#include "PowerUp.hpp"

#include "../Global/Global.hpp"

PowerUp::PowerUp(
    const PowerUpIconArgs& powerUpIconArgs, Textures::ID textureID,
    Player& player, sf::Time duration
)
    : mPlayer(player), mDuration(duration) {
    PowerUpIcon::Ptr powerUpIcon(
        new PowerUpIcon(powerUpIconArgs, textureID, mCount)
    );
    attachChild(std::move(powerUpIcon));
};

void PowerUp::start() {
    if (mIsActivated || !mCount) {
        return;
    }

    mCount--;
    mIsActivated = true;
    mRemainingDuration = mDuration;
    activate();
}

void PowerUp::increaseCount() { mCount++; }

void PowerUp::deactivate() {}

void PowerUp::updateCurrent(sf::Time deltaTime) {
    if (!mIsActivated) {
        return;
    }

    mRemainingDuration -= deltaTime * Global::DIFFICULTY_MODIFIER;

    if (mRemainingDuration <= sf::Time::Zero) {
        mIsActivated = false;
        deactivate();
    }
}

void PowerUp::saveCurrent(std::ofstream& fout) const {
    SceneNode::saveCurrent(fout);
    fout << mRemainingDuration << ' ' << mCount << ' ' << mIsActivated << '\n';
}

void PowerUp::loadCurrent(std::ifstream& fout) {
    SceneNode::loadCurrent(fout);
    fout >> mRemainingDuration >> mCount >> mIsActivated;
}
