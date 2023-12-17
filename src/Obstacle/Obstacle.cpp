#include "Obstacle.hpp"

#include "../Player/Player.hpp"

Obstacle::Obstacle(TextureHolder& textureHolder, Textures::ID texureID)
    : SpriteNode(textureHolder, texureID) {}

void Obstacle::onPlayerCollision(Player& player) { player.remainPosition(); }
