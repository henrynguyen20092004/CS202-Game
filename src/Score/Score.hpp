#ifndef SCORE_HPP
#define SCORE_HPP
#include "../Global/Global.hpp"
#include "../Player/Player.hpp"
#include "../ResourceHolder/ResourceHolder.hpp"
#include "../SceneNode/SceneNode.hpp"
#include "../TextNode/TextNode.hpp"
class Score : public SceneNode {
   private:
    Player& mPlayer;
    float highPosition;
    sf::View& mView;
    TextNode* mScoreText;
    

   public:
    void updateCurrent(sf::Time dt) override;
    typedef std::unique_ptr<Score> Ptr;
     Score(Player& player, sf::View& view, FontHolder& fontHolder);
};
#endif