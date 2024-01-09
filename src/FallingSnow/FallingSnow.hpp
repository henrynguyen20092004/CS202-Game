#ifndef FALLING_SNOW_HPP
#define FALLING_SNOW_HPP

#include "../SceneNode/SceneNode.hpp"

class FallingSnow : public SceneNode {
   public:
    typedef std::unique_ptr<FallingSnow> Ptr;

    FallingSnow(sf::View& worldView, int& seasonIndex);

   private:
    int& mSeasonIndex;

    const int mNumSnowflakes = 100;
    const sf::Time mDelayTime = sf::seconds(0.05f);
    sf::Time mTimeElapsed = sf::Time::Zero;

    sf::View& mWorldView;

    std::vector<sf::CircleShape> mSnowflakes;

    void updateCurrent(sf::Time deltaTime) override;
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const override;
};

#endif
