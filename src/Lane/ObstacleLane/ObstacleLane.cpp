#include "ObstacleLane.hpp"

#include "../../Animal/Cat/Cat.hpp"
#include "../../Animal/Cow/Cow.hpp"
#include "../../Animal/Dog/Dog.hpp"
#include "../../Animal/Horse/Horse.hpp"
#include "../../Animal/Lion/Lion.hpp"
#include "../../Global/Global.hpp"
#include "../../Obstacle/Rock/Rock.hpp"
#include "../../Obstacle/Tree/Tree.hpp"
#include "../../Random/Random.hpp"

ObstacleLane::ObstacleLane(
    TextureHolder& textureHolder, const sf::Vector2f& position,
    std::vector<PowerUpList*> powerUpList, Score* score, bool isEmpty
)
    : Lane(textureHolder, position), mPowerUpList(powerUpList), mScore(score) {
    buildScene(isEmpty);
}

void ObstacleLane::handlePlayerCollision(Player& player) {
    for (Obstacle* obstacle : mObstacles) {
        obstacle->handlePlayerCollision(player);
    }

    for (int i = 0; i < mAnimals.size(); ++i) {
        if (mAnimals[i]->collidePlayer(player)) {
            mAnimals[i]->handlePlayerCollision(player);
            mAnimals.erase(mAnimals.begin() + i);
            --i;
        }
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
    int numAnimals = Random<int>::generate({0, 1, 2}, {50, 40, 10});
    std::set<int> obstaclesPosition, animalsPosition;

    while (obstaclesPosition.size() < numObstacles) {
        obstaclesPosition.insert(Random<int>::generate(
            0, Global::WINDOW_WIDTH / Global::TILE_SIZE - 1
        ));
    }

    while (animalsPosition.size() < numAnimals) {
        int position = Random<int>::generate(
            0, Global::WINDOW_WIDTH / Global::TILE_SIZE - 1
        );

        if (obstaclesPosition.find(position) == obstaclesPosition.end()) {
            animalsPosition.insert(position);
        }
    }

    for (int position : obstaclesPosition) {
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

    for (int position : animalsPosition) {
        Animal::Ptr animal(createAnimal(Random<Textures::ID>::generate(
            {Textures::ID::Cat, Textures::ID::Dog, Textures::ID::Lion,
             Textures::ID::Cow, Textures::ID::Horse},
            {30, 30, 10, 15, 15}
        )));
        animal->setPosition(
            position * Global::TILE_SIZE +
                (Global::TILE_SIZE - animal->getSize().x) / 2.f,
            (Global::TILE_SIZE - animal->getSize().y) / 2.f
        );
        mAnimals.push_back(animal.get());
        attachChild(std::move(animal));
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

Animal* ObstacleLane::createAnimal(Textures::ID textureID) {
    switch (textureID) {
        case Textures::ID::Cat:
            return new Cat(mTextureHolder, mScore);

        case Textures::ID::Dog:
            return new Dog(mTextureHolder);

        case Textures::ID::Lion:
            return new Lion(mTextureHolder);

        case Textures::ID::Cow:
            return new Cow(mTextureHolder, mPowerUpList);

        case Textures::ID::Horse:
            return new Horse(mTextureHolder, mPowerUpList);

        default:
            return nullptr;
    }
}
