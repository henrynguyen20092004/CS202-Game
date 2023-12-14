#include "TrafficLight.hpp"

#include "../../Random/Random.hpp"

TrafficLight::TrafficLight(
    TextureHolder& textureHolder, Textures::ID textureID, Type type
)
    : speed(0), mType(type), SpriteNode(textureHolder, textureID) {
    // mType = Random<TrafficLight::Type>::generate(
    //     {TrafficLight::Type::Red, TrafficLight::Type::Yellow,
    //      TrafficLight::Type::Green}
    // );

    // this->setSprite(textureID, sf::IntRect(0, 0, 90.f, 90.f);


    // switch (mType) {
    //     case Type::Red:
            
    //         break;
    //     case Type::Yellow:
    //         setTextureRect(sf::IntRect(64, 0, 64, 64));
    //         break;
    //     case Type::Green:
    //         setTextureRect(sf::IntRect(128, 0, 64, 64));
    //         break;
    // }
}
TrafficLight::~TrafficLight() {}

void TrafficLight::drawCurrent(
    sf::RenderTarget& target, sf::RenderStates states
) const {
    states.transform *= getTransform();
    // TODO: draw traffic light
    //     target.draw(mSprite, states);
}

void TrafficLight::updateCurrent(sf::Time deltaTime) {}



void TrafficLight::setSpeed(int speed) { this->speed = speed; }

int TrafficLight::getSpeed() { return this->speed; }
