#include "ObstacleFactory.hpp"

#include "../../Global/Global.hpp"
#include "../../Obstacle/Rock/Rock.hpp"
#include "../../Random/Random.hpp"

ObstacleFactory::ObstacleFactory(TextureHolder& textureHolder, bool isEmpty)
    : Factory(textureHolder) {
    if (!isEmpty) {
        init();
    }
}

void ObstacleFactory::handlePlayerCollision(Player& player) {
    for (Obstacle* obstacle : mObstacles) {
        obstacle->handlePlayerCollision(player);
    }
}

Obstacle* ObstacleFactory::createObstacle(Textures::ID textureID) {
    switch (textureID) {
        case Textures::ID::Rock:
            return new Rock(mTextureHolder);

        default:
            return nullptr;
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
        Obstacle::Ptr obstacle(
            createObstacle(Random<Textures::ID>::generate({Textures::ID::Rock}))
        );
        obstacle->setPosition(
            position * Global::TILE_SIZE +
                (Global::TILE_SIZE - obstacle->getSize().x) / 2.f,
            (Global::TILE_SIZE - obstacle->getSize().y) / 2.f
        );
        mObstacles.push_back(obstacle.get());
        attachChild(std::move(obstacle));
    }
}
