#include "FallingSnow.hpp"

#include "../Global/Global.hpp"
#include "../Random/Random.hpp"

FallingSnow::FallingSnow(sf::View& worldView) : mWorldView(worldView) {}

void FallingSnow::updateCurrent(sf::Time deltaTime) {
    mTimeElapsed += deltaTime * Global::SPEED_MODIFIER;

    if (static_cast<Seasons::ID>(Global::SEASON_INDEX) == Seasons::ID::Winter &&
        mTimeElapsed >= mDelayTime && mSnowflakes.size() < mNumSnowflakes) {
        sf::CircleShape snowflake(Random<float>::generate(1.f, 5.f));
        snowflake.setPosition(
            Random<float>::generate(0.f, Global::WINDOW_WIDTH),
            mWorldView.getCenter().y - mWorldView.getSize().y / 2.f -
                snowflake.getRadius()
        );
        snowflake.setFillColor(sf::Color::White);

        mSnowflakes.push_back(snowflake);
        mTimeElapsed = sf::Time::Zero;
    }

    for (int i = 0; i < mSnowflakes.size(); ++i) {
        mSnowflakes[i].move(
            0.f, mSnowflakes[i].getRadius() * 0.4f * Global::SPEED_MODIFIER
        );

        if (mSnowflakes[i].getPosition().y - mSnowflakes[i].getRadius() >
            mWorldView.getCenter().y + mWorldView.getSize().y / 2.f) {
            mSnowflakes.erase(mSnowflakes.begin() + i);
        }
    }
}

void FallingSnow::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
    const {
    for (const auto& snowflake : mSnowflakes) {
        target.draw(snowflake, states);
    }
}
