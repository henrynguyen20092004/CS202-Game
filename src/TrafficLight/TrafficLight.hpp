#ifndef TRAFFIC_LIGHT_HPP
#define TRAFFIC_LIGHT_HPP

#include "../Obstacle/Obstacle.hpp"

class TrafficLight : public Obstacle {
   private:
    int direction;
    int speed;
    int color;
    int width;
    int height;
    int x;
    int y;

   public:
    TrafficLight();
    TrafficLight(
        int x, int y, int width, int height, int speed, int direction, int color
    );
    ~TrafficLight();

    void draw(sf::RenderWindow &window);
    void setDirection(int direction);
    void setSpeed(int speed);
    void setColor(int color);
    void setWidth(int width);
    void setHeight(int height);
    void setX(int x);
    void setY(int y);
    int getDirection();
    int getSpeed();
    int getColor();
    int getWidth();
    int getHeight();
    int getX();
    int getY();
};

#endif  // TRAFFICLIGHT_HPP
