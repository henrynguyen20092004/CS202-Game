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
        const std::vector<PowerUpList*>& powerUpList, Score* score,
        bool isLoading, bool isEmpty = false
    );

   private:
    std::vector<PowerUpList*> mPowerUpList;
    std::vector<Obstacle*> mObstacles;
    std::vector<Animal*> mAnimals;
    Score* mScore;

    void handlePlayerCollision(Player& player) override;

    void buildScene(bool isLoading);

    void init();

    Obstacle* createObstacle(Textures::ID textureID);
    Animal* createAnimal(Textures::ID textureID);

    Textures::ID getTextureID() const final;

    void saveCurrent(std::ofstream& fout) const final;
    void loadCurrent(std::ifstream& fin) final;
};

#endif
