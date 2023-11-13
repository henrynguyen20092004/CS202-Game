#include "TrafficLight.hpp"

TrafficLight::TrafficLight() {
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    this->speed = 0;
    this->direction = 0;
    this->color = 0;
}

TrafficLight::TrafficLight(
    int x, int y, int width, int height, int speed, int direction, int color
) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->speed = speed;
    this->direction = direction;
    this->color = color;
}

TrafficLight::~TrafficLight() {}

void TrafficLight::draw(sf::RenderWindow &window) {
    sf::RectangleShape trafficLight(sf::Vector2f(this->width, this->height));
    trafficLight.setPosition(this->x, this->y);
    trafficLight.setFillColor(sf::Color(this->color, this->color, this->color));
    window.draw(trafficLight);
}

    

void TrafficLight::setDirection(int direction) {
    this->direction = direction;
}

void TrafficLight::setSpeed(int speed) {
    this->speed = speed;
}

void TrafficLight::setColor(int color) {
    this->color = color;
}

void TrafficLight::setWidth(int width) {
    this->width = width;
}

void TrafficLight::setHeight(int height) {
    this->height = height;
}

void TrafficLight::setX(int x) {
    this->x = x;
}

void TrafficLight::setY(int y) {
    this->y = y;
}

int TrafficLight::getDirection() {
    return this->direction;
}

int TrafficLight::getSpeed() {
    return this->speed;
}

int TrafficLight::getColor() {
    return this->color;
}

int TrafficLight::getWidth() {
    return this->width;
}

int TrafficLight::getHeight() {
    return this->height;
}

int TrafficLight::getX() {
    return this->x;
}

int TrafficLight::getY() {
    return this->y;
}
