#include "SlowTime.hpp"

#include "../../Global/Global.hpp"

#define SLOW_FACTOR 10

SlowTime::SlowTime(Player& player) : PowerUp(sf::seconds(10.f), player) {}

void SlowTime::activate() { Global::SPEED_MODIFIER /= SLOW_FACTOR; }

void SlowTime::deactivate() { Global::SPEED_MODIFIER *= SLOW_FACTOR; }
