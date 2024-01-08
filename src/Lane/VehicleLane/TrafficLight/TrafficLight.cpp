#include "TrafficLight.hpp"

#include "../../../FileIO/FileIO.hpp"
#include "../../../Global/Global.hpp"
#include "../../../Random/Random.hpp"

TrafficLight::TrafficLight(
    TextureHolder& mTextureHolder, Directions::ID direction, bool isLoading
)
    : SpriteNode(mTextureHolder, Textures::ID::TrafficLight) {
    if (isLoading) {
        return;
    }

    mState = Random<TrafficLight::State>::generate(
        {TrafficLight::State::Red, TrafficLight::State::Yellow,
         TrafficLight::State::Green}
    );

    sf::Vector2u textureSize =
        mTextureHolder.get(Textures::ID::TrafficLight).getSize();

    setPosition(
        direction == Directions::ID::Left
            ? Global::WINDOW_WIDTH - Global::TILE_SIZE -
                  textureSize.x / StateCount
            : Global::TILE_SIZE,
        0
    );

    setTextureRect(sf::IntRect(
        textureSize.x * mState / StateCount, 0, textureSize.x / StateCount,
        textureSize.y
    ));
}

TrafficLight::State TrafficLight::getState() const { return mState; }

void TrafficLight::switchState(TrafficLight::State state) {
    switch (state) {
        case TrafficLight::State::Red:
            mState = TrafficLight::State::Green;
            break;

        case TrafficLight::State::Yellow:
            mState = TrafficLight::State::Red;
            break;

        case TrafficLight::State::Green:
            mState = TrafficLight::State::Yellow;
            break;

        default:
            break;
    }
}

void TrafficLight::updateCurrent(sf::Time deltaTime) {
    mTimeCount +=
        deltaTime * Global::SPEED_MODIFIER * Global::DIFFICULTY_MODIFIER;

    sf::Vector2u textureSize =
        mTextureHolder.get(Textures::ID::TrafficLight).getSize();

    if (mTimeCount.asSeconds() >= mStateTimeCount[mState].asSeconds()) {
        switchState(mState);
        mTimeCount = sf::Time::Zero;
    }

    setTextureRect(sf::IntRect(
        textureSize.x * mState / StateCount, 0, textureSize.x / StateCount,
        textureSize.y
    ));
}

void TrafficLight::saveCurrent(std::ofstream& fout) const {
    SpriteNode::saveCurrent(fout);
    fout << mState << ' ';
    fout << mTimeCount << '\n';
}

void TrafficLight::loadCurrent(std::ifstream& fin) {
    SpriteNode::loadCurrent(fin);
    int state;
    fin >> state;
    mState = static_cast<TrafficLight::State>(state);

    fin >> mTimeCount;
}
