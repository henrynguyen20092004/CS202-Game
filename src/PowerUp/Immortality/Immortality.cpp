#include "Immortality.hpp"

Immortality::Immortality(const PowerUpIconArgs& powerUpIconArgs, Player& player)
    : PowerUp(powerUpIconArgs, Textures::ID::Horse, player, sf::seconds(10.f)) {}

void Immortality::activate() { mPlayer.setImortal(true); }

void Immortality::deactivate() { mPlayer.setImortal(false); }
