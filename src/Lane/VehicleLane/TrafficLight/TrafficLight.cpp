#include "TrafficLight.hpp"

#include "../../../Global/Global.hpp"
#include "../../../Random/Random.hpp"

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
        setPosition(
            Global::WINDOW_WIDTH - Global::TILE_SIZE - textureSize.x / 3, 0
        );
    } else {
        setPosition(Global::TILE_SIZE, 0);
    }

    mSprite.setTextureRect(sf::IntRect(
        textureSize.x * mState / 3, 0, textureSize.x / 3, textureSize.y
    ));
}

TrafficLight::State TrafficLight::getState() const { return mState; }

void TrafficLight::switchState(TrafficLight::State state) {
    mState = static_cast<State>((mState + 2) % 3);
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

    mSprite.setTextureRect(sf::IntRect(
        textureSize.x * mState / 3, 0, textureSize.x / 3, textureSize.y
    ));
}
