#include "PolarBear.hpp"

PolarBear::PolarBear(
    TextureHolder& TextureHolder, Textures::ID textureID,
    PowerUpList& powerUpList
)
    : Animal(TextureHolder, textureID, powerUpList, 1, sf::seconds(1.f)) {
    setHitbox(getLocalBounds());  // TODO: Set hitbox properly
}

PowerUp::Type PolarBear::getPowerUpType() const {
    return PowerUp::Type::SlowTime;
}
