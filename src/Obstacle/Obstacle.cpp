#include "Obstacle.hpp"

#include "../Player/Player.hpp"

void Obstacle::handlePlayerCollision(Player& player) {
    if (!player.isImmortal() && collidePlayer(player)) {
        player.goBack();
    }
}
