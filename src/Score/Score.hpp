#ifndef SCORE_HPP
#define SCORE_HPP

#include "../Player/Player.hpp"
#include "../PowerUpList/PowerUpList.hpp"
#include "../TextNode/TextNode.hpp"

class Score : public SceneNode {
   public:
    typedef std::unique_ptr<Score> Ptr;

    Score(Player& player, sf::View& worldView, FontHolder& fontHolder);

    void init();

    void addBonus();

   private:
    Player& mPlayer;
    sf::View& mWorldView;
    TextNode* mScoreText;
    float mInitialPlayerPosition = 0, mHighestPlayerPosition = 0;
    int mBonus = 0;

    void updateCurrent(sf::Time deltaTime) override;

    void saveCurrent(std::ofstream& fout) const final;
    void loadCurrent(std::ifstream& fin) final;
};

#endif
