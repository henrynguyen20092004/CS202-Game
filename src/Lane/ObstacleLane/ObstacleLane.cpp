#include "ObstacleLane.hpp"

#include "../../Global/Global.hpp"
#include "../../Obstacle/Rock/Rock.hpp"
#include "../../Obstacle/Tree/Tree.hpp"
#include "../../Random/Random.hpp"

ObstacleLane::ObstacleLane(
    TextureHolder& textureHolder, const sf::Vector2f& position, bool isEmpty
)
    : Lane(textureHolder, position) {
    buildScene(isEmpty);
}

void ObstacleLane::handlePlayerCollision(Player& player) {
    for (Obstacle* obstacle : mObstacles) {
        obstacle->handlePlayerCollision(player);
    }
}

void ObstacleLane::buildScene(bool isEmpty) {
    Lane::buildScene(Textures::ID::ObstacleLane);

    for (int i = 0; i < Global::NUM_TILES_X; ++i) {
        SpriteNode::Ptr sprite(new SpriteNode(
            mTextureHolder, Textures::ID::ObstacleLane,
            sf::IntRect(
                Random<int>::generate({0, 1, 2, 3, 4}, {70, 5, 5, 10, 10}) *
                    Global::TILE_SIZE,
                0, Global::TILE_SIZE, Global::TILE_SIZE
            )
        ));
        sprite->setPosition(i * Global::TILE_SIZE, 0.f);
        mSceneLayers[LaneLayer]->attachChild(std::move(sprite));
    }

    if (!isEmpty) {
        init();
    }
}

void ObstacleLane::init() {
    int numObstacles = Random<int>::generate(0, 5);
    std::set<int> positions;

    while (positions.size() < numObstacles) {
        positions.insert(Random<int>::generate(
            0, Global::WINDOW_WIDTH / Global::TILE_SIZE - 1
        ));
    }

    for (int position : positions) {
        Obstacle::Ptr obstacle(createObstacle(Random<Textures::ID>::generate(
            {Textures::ID::Rock, Textures::ID::Tree}, {50, 50}
        )));
        obstacle->setPosition(
            position * Global::TILE_SIZE +
                (Global::TILE_SIZE - obstacle->getSize().x) / 2.f,
            (Global::TILE_SIZE - obstacle->getSize().y) / 2.f
        );
        mObstacles.push_back(obstacle.get());
        attachChild(std::move(obstacle));
    }
}

Obstacle* ObstacleLane::createObstacle(Textures::ID textureID) {
    switch (textureID) {
        case Textures::ID::Rock:
            return new Rock(mTextureHolder);

        case Textures::ID::Tree:
            return new Tree(mTextureHolder);

        default:
            return nullptr;
    }
}
