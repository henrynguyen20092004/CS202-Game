#ifndef TRAFFIC_LIGHT_HPP
#define TRAFFIC_LIGHT_HPP

#include "../../ResourceHolder/ResourceHolder.hpp"
#include "../../SpriteNode/SpriteNode.hpp"
#include "../Obstacle.hpp"

class TrafficLight : public SpriteNode {
   public:
    TrafficLight(TextureHolder& textureHolder, Textures::ID texureID);

    void setSpeed(int speed);
    int getSpeed();
    void updateCurrent(sf::Time deltaTime) override;

   private:
    enum class Type {
        Red,
        Yellow,
        Green,
        None,
    };
    typedef std::unique_ptr<TrafficLight> Ptr;
    Type mType;
    int speed;
};

#endif  // TRAFFICLIGHT_HPP
