#include "Regenerate.hpp"

#include "../../Global/Global.hpp"

Regenerate::Regenerate(const PowerUpIconArgs& powerUpIconArgs, Player& player)
    : PowerUp(
          powerUpIconArgs, Textures::ID::Phoenix, player, sf::seconds(10.f)
      ) {}

void Regenerate::activate() {}

void Regenerate::deactivate() {}
