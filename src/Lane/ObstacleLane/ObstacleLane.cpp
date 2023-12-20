#include "ObstacleLane.hpp"

#include "../../Factory/ObstacleFactory/ObstacleFactory.hpp"

ObstacleLane::ObstacleLane(
    TextureHolder& textureHolder, const sf::Vector2f& position, bool isEmpty
)
    : Lane(textureHolder, position) {
    buildScene(isEmpty);
}

void ObstacleLane::buildScene(bool isEmpty) {
    Lane::buildScene(Textures::ID::ObstacleLane);
    Factory::Ptr factory(new ObstacleFactory(mTextureHolder, isEmpty));
    mSceneLayers[ObjectLayer]->attachChild(std::move(factory));
}
