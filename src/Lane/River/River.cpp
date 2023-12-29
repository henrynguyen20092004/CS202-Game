#include "River.hpp"

#include "../../Factory/LogFactory/LogFactory.hpp"

River::River(TextureHolder& textureHolder, const sf::Vector2f& position)
    : Lane(textureHolder, position) {
    buildScene();
}

void River::buildScene() {
    Lane::buildScene(Textures::ID::River);

    LogFactory::Ptr factory(new LogFactory(mTextureHolder));
    mSceneLayers[FactoryLayer]->attachChild(std::move(factory));
}
