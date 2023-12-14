#include "TrafficLight.hpp"

#include "../../Random/Random.hpp"

TrafficLight::TrafficLight(TextureHolder& textureHolder, Textures::ID textureID)
    : speed(0), SpriteNode(textureHolder, textureID) {
    mType = Random<TrafficLight::Type>::generate(
        {TrafficLight::Type::Red, TrafficLight::Type::Yellow,
         TrafficLight::Type::Green}
    );

    sf::Vector2u textureSize = textureHolder.get(textureID).getSize();

    switch (mType) {
        case Type::Red:
            this->setSprite(
                textureID, sf::IntRect(0, 0, textureSize.x / 3, textureSize.y)
            );
            break;
        case Type::Yellow:
            this->setSprite(
                textureID,
                sf::IntRect(
                    textureSize.x / 3, 0, textureSize.x / 3, textureSize.y
                )
            );
            break;
        case Type::Green:
            this->setSprite(
                textureID,
                sf::IntRect(
                    textureSize.x * 2 / 3, 0, textureSize.x / 3, textureSize.y
                )
            );
            break;
        default:
            break;
    }
}

void TrafficLight::updateCurrent(sf::Time deltaTime) {}

void TrafficLight::setSpeed(int speed) { this->speed = speed; }

int TrafficLight::getSpeed() { return this->speed; }
