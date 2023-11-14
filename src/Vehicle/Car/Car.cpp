#include "Car.hpp"

Car::Car(Directions::ID direction, float speed, TextureHolder& textureHolder)
    : Vehicle(direction, speed) {
    mSprite.setTexture(textureHolder.get(Textures::ID::Car));
}
