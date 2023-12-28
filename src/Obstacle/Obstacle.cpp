#include "Obstacle.hpp"

#include "../Player/Player.hpp"

void Obstacle::handlePlayerCollision(Player& player) {
    if (collidePlayer(player)) {
        player.remainPosition();
    }
}
