#ifndef OBSTACLE_LANE_HPP
#define OBSTACLE_LANE_HPP

#include "../../Animal/Animal.hpp"
#include "../../Obstacle/Obstacle.hpp"
#include "../../PowerUpList/PowerUpList.hpp"
#include "../../Score/Score.hpp"
#include "../Lane.hpp"

class ObstacleLane : public Lane {
   public:
    ObstacleLane(
        TextureHolder& textureHolder, const sf::Vector2f& position,
        std::vector<PowerUpList*> powerUpList, Score* score,
        bool isEmpty = false
    );

   private:
    std::vector<PowerUpList*> mPowerUpList;
    Score* mScore;
    std::vector<Obstacle*> mObstacles;
    std::vector<Animal*> mAnimals;

    void handlePlayerCollision(Player& player) override;

    void buildScene(bool isEmpty);

    void init();

    Obstacle* createObstacle(Textures::ID textureID);
    Animal* createAnimal(Textures::ID textureID);
};

#endif
