#include "SlowTime.hpp"

#include "../../Global/Global.hpp"

#define SLOW_FACTOR 10

SlowTime::SlowTime(const PowerUpIconArgs& powerUpIconArgs, Player& player)
    : PowerUp(
          powerUpIconArgs, Textures::ID::PolarBear, player, sf::seconds(10.f)
      ) {}

void SlowTime::activate() { Global::SPEED_MODIFIER /= SLOW_FACTOR; }

void SlowTime::deactivate() { Global::SPEED_MODIFIER *= SLOW_FACTOR; }
