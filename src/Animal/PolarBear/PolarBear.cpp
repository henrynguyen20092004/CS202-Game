#include "PolarBear.hpp"

#include "../../Player/Player.hpp"

PolarBear::PolarBear(
    TextureHolder& TextureHolder, Textures::ID textureID, sf::View& worldView,
    PowerUpList& powerUpList
)
    : Animal(TextureHolder, textureID, worldView, powerUpList) {}

PowerUp::Type PolarBear::getPowerUpType() const {
    return PowerUp::Type::SlowTime;
}
