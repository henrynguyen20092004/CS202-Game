#include "Immortality.hpp"

Immortality::Immortality(const PowerUpIconArgs& powerUpIconArgs, Player& player)
    : PowerUp(powerUpIconArgs, Textures::ID::Pug, player, sf::seconds(-1.f)) {}

void Immortality::activate() { mPlayer.setImmortalTime(sf::seconds(10.f)); }
