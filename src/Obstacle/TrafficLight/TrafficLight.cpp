#include "TrafficLight.hpp"

TrafficLight::TrafficLight(Type type): speed(0), mType(type) {}
TrafficLight::~TrafficLight() {}

void TrafficLight::draw(sf::RenderTarget& target, sf::RenderStates states)
    const {
    states.transform *= getTransform();
    // TODO: draw traffic light
    //     target.draw(mSprite, states);
}

void TrafficLight::update(float deltaTime){
    //after a period of time, change the color of the traffic light
    //3 colors: red, yellow, green
    //red: speed = 0
    //yellow: speed = 1
    //green: speed = 2
    
}

void TrafficLight::setSpeed(int speed) { this->speed = speed; }

int TrafficLight::getSpeed() { return this->speed; }

