#include "TrafficLight.hpp"

#include "../../Global/Global.hpp"
#include "../../Random/Random.hpp"

TrafficLight::TrafficLight(
    TextureHolder& mTextureHolder, Directions::ID direction
)
    : SpriteNode(mTextureHolder, Textures::ID::TrafficLight) {
    mState = Random<TrafficLight::State>::generate(
        {TrafficLight::State::Red, TrafficLight::State::Yellow,
         TrafficLight::State::Green}
    );

    sf::Vector2u textureSize =
        mTextureHolder.get(Textures::ID::TrafficLight).getSize();

    if (direction == Directions::ID::Left) {
        this->setPosition(Global::WINDOW_WIDTH - this->getSize().x, 0);
    } else {
        this->setPosition(this->getSize().x, 0);
    }

    this->setTextureRect(sf::IntRect(
        textureSize.x * static_cast<int>(mState) / 3, 0, textureSize.x / 3,
        textureSize.y
    ));
}

TrafficLight::State TrafficLight::getState() const { return mState; }

void TrafficLight::switchState(TrafficLight::State state) {
    switch (mState) {
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
    mTimeCount += deltaTime;
    sf::Vector2u textureSize =
        mTextureHolder.get(Textures::ID::TrafficLight).getSize();

    if (mTimeCount.asSeconds() >=
        mStateTimeCount[static_cast<int>(mState)].asSeconds()) {
        switchState(mState);
        mTimeCount = sf::Time::Zero;
    }

    this->setTextureRect(sf::IntRect(
        textureSize.x * static_cast<int>(mState) / 3, 0, textureSize.x / 3,
        textureSize.y
    ));
}
