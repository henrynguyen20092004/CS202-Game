#include "Obstacle.hpp"

#include "../Player/Player.hpp"

void Obstacle::onPlayerCollision(Player& player) { player.remainPosition(); }
