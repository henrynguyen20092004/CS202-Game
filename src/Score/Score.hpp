#ifndef SCORE_HPP
#define SCORE_HPP

#include "../Player/Player.hpp"
#include "../PowerUpList/PowerUpList.hpp"
#include "../TextNode/TextNode.hpp"

class Score : public SceneNode {
   public:
    typedef std::unique_ptr<Score> Ptr;

    Score(Player& player, sf::View& view, FontHolder& fontHolder);

    void addBonus();

   private:
    Player& mPlayer;
    sf::View& mView;
    TextNode* mScoreText;
    float mInitialPlayerPosition, mHighestPlayerPosition;
    int mBonus = 0;

    int getScore();
    void updateCurrent(sf::Time deltaTime) override;
};

#endif
