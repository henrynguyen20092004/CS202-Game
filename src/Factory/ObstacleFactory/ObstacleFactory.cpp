#include "ObstacleFactory.hpp"

#include "../../Global/Global.hpp"
#include "../../Random/Random.hpp"

ObstacleFactory::ObstacleFactory(TextureHolder& textureHolder, bool isEmpty)
    : Factory(textureHolder) {
    if (!isEmpty) {
        init();
    }
}

void ObstacleFactory::init() {
    int numObstacles = Random<int>::generate(0, 10);
    std::set<int> positions;

    while (positions.size() < numObstacles) {
        positions.insert(Random<int>::generate(
            0, Global::WINDOW_WIDTH / Global::TILE_SIZE - 1
        ));
    }

    for (int position : positions) {
        Textures::ID textureID =
            Random<Textures::ID>::generate({Textures::ID::Rock});
        Obstacle::Ptr obstacle(new Obstacle(mTextureHolder, textureID));
        obstacle->setPosition(
            position * Global::TILE_SIZE +
                (Global::TILE_SIZE - obstacle->getSize().x) / 2.f,
            (Global::TILE_SIZE - obstacle->getSize().y) / 2.f
        );
        attachChild(std::move(obstacle));
    }
}
