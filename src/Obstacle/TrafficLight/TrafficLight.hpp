#ifndef TRAFFIC_LIGHT_HPP
#define TRAFFIC_LIGHT_HPP

#include <array>

#include "../../SpriteNode/SpriteNode.hpp"

class TrafficLight : public SpriteNode {
   public:
    typedef std::unique_ptr<TrafficLight> Ptr;

    TrafficLight(TextureHolder& mTextureHolder, Directions::ID direction);

    TrafficLightStates::ID getState() const;

   private:
    const std::array<sf::Time, 3> mStateTimeCount{
        sf::seconds(2), sf::seconds(1), sf::seconds(2)
    };
    TrafficLightStates::ID mState;
    sf::Time mTimeCount;

    void switchState(TrafficLightStates::ID state);
    void updateCurrent(sf::Time deltaTime) override;
};

#endif
