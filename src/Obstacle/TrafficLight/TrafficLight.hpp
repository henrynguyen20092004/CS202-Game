#ifndef TRAFFIC_LIGHT_HPP
#define TRAFFIC_LIGHT_HPP

#include "../../ResourceHolder/ResourceHolder.hpp"
#include "../../SpriteNode/SpriteNode.hpp"
#include "../Obstacle.hpp"
#include "../../Identifier/Identifier.hpp"

class TrafficLight : public SpriteNode {
   public:
    typedef std::unique_ptr<TrafficLight> Ptr;

    TrafficLight(TextureHolder& mTextureHolder, Directions::ID direction);

    TrafficLightStates::ID getState() const;

   private:
    TrafficLightStates::ID mState;
    sf::Time mTimeCount;

    void updateCurrent(sf::Time deltaTime) override;
};

#endif
