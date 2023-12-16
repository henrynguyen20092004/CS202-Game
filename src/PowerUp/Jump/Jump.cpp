#include "Jump.hpp"

Jump::Jump(Player& player)
    : PowerUp(sf::seconds(10.f), player) {}

void Jump::activate() {}

void Jump::deactivate() {}
