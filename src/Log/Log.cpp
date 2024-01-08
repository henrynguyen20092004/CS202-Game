#include "Log.hpp"

Log::Log(
    TextureHolder& textureHolder, Textures::ID textureID,
    sf::IntRect textureRect, Directions::ID direction
)
    : MovableSpriteNode(textureHolder, textureID, textureRect),
      mDirection(direction) {}

void Log::updateCurrent(sf::Time deltaTime) {
    switch (mDirection) {
        case Directions::ID::Left:
            MovableSpriteNode::updateCurrent(-deltaTime);
            break;

        case Directions::ID::Right:
            MovableSpriteNode::updateCurrent(deltaTime);
            break;

        default:
            break;
    }
}

void Log::saveCurrent(std::ofstream& fout) const {
    MovableSpriteNode::saveCurrent(fout);
    fout << static_cast<int>(mDirection) << '\n';
}

void Log::loadCurrent(std::ifstream& fin) {
    MovableSpriteNode::loadCurrent(fin);
    int direction;
    fin >> direction;
    mDirection = static_cast<Directions::ID>(direction);
}
