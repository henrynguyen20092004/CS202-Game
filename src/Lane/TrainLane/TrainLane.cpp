#include "TrainLane.hpp"

#include "../../Factory/TrainFactory/TrainFactory.hpp"

TrainLane::TrainLane(TextureHolder& textureHolder, const sf::Vector2f& position)
    : Lane(textureHolder, position) {
    buildScene();
}

void TrainLane::handlePlayerCollision(Player& player) {
    mTrainFactory->handlePlayerCollision(player);
}

void TrainLane::buildScene() {
    Lane::buildScene(Textures::ID::TrainLane);

    TrainFactory::Ptr factory(new TrainFactory(mTextureHolder));
    mTrainFactory = factory.get();
    mSceneLayers[FactoryLayer]->attachChild(std::move(factory));
}
