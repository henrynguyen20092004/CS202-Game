#include "TrafficLight.hpp"

#include "../../Global/Global.hpp"
#include "../../Random/Random.hpp"

TrafficLight::TrafficLight(
    TextureHolder& mTextureHolder, Directions::ID direction
)
    : speed(0), SpriteNode(mTextureHolder, Textures::ID::TrafficLight) {
    mTimeCount = sf::Time::Zero;
    mType = Random<TrafficLight::Type>::generate(
        {TrafficLight::Type::Red, TrafficLight::Type::Yellow,
         TrafficLight::Type::Green}
    );

    sf::Vector2u textureSize =
        mTextureHolder.get(Textures::ID::TrafficLight).getSize();
    if (direction == Directions::ID::Left) {
        this->setPosition(Global::WINDOW_WIDTH - this->getSize().x, 0);
    } else {
        this->setPosition(this->getSize().x, 0);
    }

    switch (mType) {
        case Type::Red:
            this->setSprite(
                Textures::ID::TrafficLight,
                sf::IntRect(0, 0, textureSize.x / 3, textureSize.y)
            );
            break;

        case Type::Yellow:
            this->setSprite(
                Textures::ID::TrafficLight,
                sf::IntRect(
                    textureSize.x / 3, 0, textureSize.x / 3, textureSize.y
                )
            );
            break;

        case Type::Green:
            this->setSprite(
                Textures::ID::TrafficLight,
                sf::IntRect(
                    textureSize.x * 2 / 3, 0, textureSize.x / 3, textureSize.y
                )
            );
            break;

        default:
            break;
    }
}

void TrafficLight::updateCurrent(sf::Time deltaTime) {
    mTimeCount += deltaTime;
    sf::Vector2u textureSize =
        mTextureHolder.get(Textures::ID::TrafficLight).getSize();
    if (mTimeCount.asSeconds() >= 2) {
        mTimeCount = sf::Time::Zero;
        switch (mType) {
            case Type::Red:
                mType = Type::Green;
                this->setSprite(
                    Textures::ID::TrafficLight,
                    sf::IntRect(
                        textureSize.x * 2 / 3, 0, textureSize.x / 3,
                        textureSize.y
                    )
                );

                break;

            case Type::Yellow:
                mType = Type::Red;
                this->setSprite(
                    Textures::ID::TrafficLight,
                    sf::IntRect(0, 0, textureSize.x / 3, textureSize.y)
                );
                break;

            case Type::Green:
                mType = Type::Yellow;
                this->setSprite(
                    Textures::ID::TrafficLight,
                    sf::IntRect(
                        textureSize.x / 3, 0, textureSize.x / 3, textureSize.y
                    )
                );
                break;

            default:
                break;
        }
    }
}

void TrafficLight::setSpeed(int speed) { this->speed = speed; }

int TrafficLight::getSpeed() { return this->speed; }
