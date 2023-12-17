#include "TrafficLight.hpp"

#include "../../Global/Global.hpp"
#include "../../Random/Random.hpp"

TrafficLight::TrafficLight(
    TextureHolder& mTextureHolder, Directions::ID direction
)
    : SpriteNode(mTextureHolder, Textures::ID::TrafficLight) {
    mTimeCount = sf::Time::Zero;
    mState = Random<TrafficLightStates::ID>::generate(
        {TrafficLightStates::ID::Red, TrafficLightStates::ID::Yellow,
         TrafficLightStates::ID::Green}
    );

    sf::Vector2u textureSize =
        mTextureHolder.get(Textures::ID::TrafficLight).getSize();

    if (direction == Directions::ID::Left) {
        this->setPosition(Global::WINDOW_WIDTH - this->getSize().x, 0);
    } else {
        this->setPosition(this->getSize().x, 0);
    }

    this->setSprite(
        Textures::ID::TrafficLight,
        sf::IntRect(
            textureSize.x * static_cast<int>(mState) / 3, 0, textureSize.x / 3,
            textureSize.y
        )
    );
}

TrafficLightStates::ID TrafficLight::getState() const { return mState; }

void TrafficLight::switchState(TrafficLightStates::ID state) {
    switch (mState) {
        case TrafficLightStates::ID::Red:
            mState = TrafficLightStates::ID::Green;
            break;

        case TrafficLightStates::ID::Yellow:
            mState = TrafficLightStates::ID::Red;
            break;

        case TrafficLightStates::ID::Green:
            mState = TrafficLightStates::ID::Yellow;
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

    this->setSprite(
        Textures::ID::TrafficLight,
        sf::IntRect(
            textureSize.x * static_cast<int>(mState) / 3, 0, textureSize.x / 3,
            textureSize.y
        )
    );
}
