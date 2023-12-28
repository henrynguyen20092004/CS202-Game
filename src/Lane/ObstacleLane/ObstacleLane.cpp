#include "ObstacleLane.hpp"

ObstacleLane::ObstacleLane(
    TextureHolder& textureHolder, const sf::Vector2f& position, bool isEmpty
)
    : Lane(textureHolder, position) {
    buildScene(isEmpty);
}

void ObstacleLane::handlePlayerCollision(Player& player) {
    mObstacleFactory->handlePlayerCollision(player);
}

void ObstacleLane::buildScene(bool isEmpty) {
    Lane::buildScene(Textures::ID::ObstacleLane);

    ObstacleFactory::Ptr factory(new ObstacleFactory(mTextureHolder, isEmpty));
    mObstacleFactory = factory.get();
    mSceneLayers[ObjectLayer]->attachChild(std::move(factory));
}
