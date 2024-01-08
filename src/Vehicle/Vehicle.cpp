#include "Vehicle.hpp"

#include "../Player/Player.hpp"

Vehicle::Vehicle(
    TextureHolder& textureHolder, Textures::ID textureID,
    Directions::ID direction
)
    : Entity(textureHolder, textureID), mDirection(direction) {}

Directions::ID Vehicle::getDirection() const { return mDirection; }

void Vehicle::setDirection(Directions::ID direction) { mDirection = direction; }

void Vehicle::handlePlayerCollision(Player& player) {
    if (!player.isImmortal() && collidePlayer(player)) {
        player.damage();
    }
}

void Vehicle::updateCurrent(sf::Time deltaTime) {
    switch (mDirection) {
        case Directions::ID::Left:
            Entity::updateCurrent(-deltaTime);
            break;

        case Directions::ID::Right:
            Entity::updateCurrent(deltaTime);
            break;

        default:
            break;
    }
}

void Vehicle::saveCurrent(std::ofstream& fout) const {
    Entity::saveCurrent(fout);
    fout << static_cast<int>(mDirection) << '\n';
}

void Vehicle::loadCurrent(std::ifstream& fin) {
    Entity::loadCurrent(fin);
    int direction;
    fin >> direction;
    mDirection = static_cast<Directions::ID>(direction);
}
