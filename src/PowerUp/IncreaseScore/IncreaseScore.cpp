#include "IncreaseScore.hpp"

IncreaseScore::IncreaseScore(Player& player)
    : PowerUp(sf::seconds(10.f), player) {}

void IncreaseScore::activate() {}

void IncreaseScore::deactivate() {}
