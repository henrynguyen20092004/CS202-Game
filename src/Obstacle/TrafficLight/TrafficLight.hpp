#ifndef TRAFFIC_LIGHT_HPP
#define TRAFFIC_LIGHT_HPP

#include "../Obstacle.hpp"

class TrafficLight : public Obstacle {
   private:
    enum class Type {
        Red,
        Yellow,
        Green,
    };
    Type mType;
    int speed;


   public:
    TrafficLight(Type type);
    ~TrafficLight();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setSpeed(int speed);
    int getSpeed();
    void update(float deltaTime) override;
};

#endif  // TRAFFICLIGHT_HPP
