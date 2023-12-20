#include "PolarBear.hpp"

PolarBear::PolarBear(
    TextureHolder& TextureHolder, Textures::ID textureID,
    PowerUpList& powerUpList
)
    : Animal(TextureHolder, textureID, powerUpList, 1, sf::seconds(1.f)) {}

PowerUp::Type PolarBear::getPowerUpType() const {
    return PowerUp::Type::SlowTime;
}
