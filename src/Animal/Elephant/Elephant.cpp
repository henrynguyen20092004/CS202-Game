#include "Elephant.hpp"

Elephant::Elephant(
    TextureHolder& textureHolder, Textures::ID textureID,
    PowerUpList& powerUpList
)
    : Animal(textureHolder, textureID, powerUpList, 10, sf::seconds(2.f)) {}

PowerUp::Type Elephant::getPowerUpType() const {
    return PowerUp::Type::BonusHealth;
}
