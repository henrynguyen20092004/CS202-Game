#include "TrainLane.hpp"

#include "../../Factory/TrainFactory/TrainFactory.hpp"

TrainLane::TrainLane(TextureHolder& textureHolder, const sf::Vector2f& position)
    : Lane(textureHolder, position) {
    buildScene();
}

void TrainLane::buildScene() {
    Lane::buildScene(Textures::ID::TrainLane);
    Factory::Ptr factory(new TrainFactory(mTextureHolder));
    mSceneLayers[ObjectLayer]->attachChild(std::move(factory));
}
