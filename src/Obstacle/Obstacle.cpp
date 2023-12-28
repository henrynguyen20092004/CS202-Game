#include "Obstacle.hpp"

#include "../Player/Player.hpp"

Obstacle::Obstacle(TextureHolder& textureHolder) : Entity(textureHolder) {}

void Obstacle::handlePlayerCollision(Player& player) {
    if (collidePlayer(player)) {
        player.remainPosition();
    }
}
