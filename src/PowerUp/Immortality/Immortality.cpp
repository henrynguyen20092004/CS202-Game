#include "Immortality.hpp"

Immortality::Immortality(const PowerUpIconArgs& powerUpIconArgs, Player& player)
    : PowerUp(powerUpIconArgs, Textures::ID::Pug, player, sf::seconds(10.f)) {}

void Immortality::activate() { mPlayer.setImmortal(true); }

void Immortality::deactivate() { mPlayer.setImmortal(false); }
