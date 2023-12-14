#ifndef TRAFFIC_LIGHT_HPP
#define TRAFFIC_LIGHT_HPP

#include "../../ResourceHolder/ResourceHolder.hpp"
#include "../../SpriteNode/SpriteNode.hpp"
#include "../Obstacle.hpp"

class TrafficLight : public SpriteNode {
   private:
    enum class Type {
        Red,
        Yellow,
        Green,
    };
    Type mType;
    int speed;

   public:
    TrafficLight(
        TextureHolder& textureHolder, Textures::ID texureID, Type type
    );
    ~TrafficLight();

    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const override;
    void setSpeed(int speed);
    int getSpeed();
    void updateCurrent(sf::Time deltaTime) override;
};

#endif  // TRAFFICLIGHT_HPP
