#include "BonusHealth.hpp"

BonusHealth::BonusHealth(Player& player) : PowerUp(sf::seconds(-1.f), player) {}

void BonusHealth::activate() { mPlayer.heal(); }
