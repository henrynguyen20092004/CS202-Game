#include "Score.hpp"

Score::Score(Player& player, sf::View& view, FontHolder& fontHolder)
    : mPlayer(player), mView(view) {
    highPosition = mPlayer.getPosition().y;
    TextNode::Ptr textnode(new TextNode(fontHolder, "Score: 0"));
    mScoreText = textnode.get();
    attachChild(std::move(textnode));
   bonus = 0;
}

void Score::updateCurrent(sf::Time dt) {
    if (mPlayer.getPosition().y < highPosition) {
        highPosition = mPlayer.getPosition().y;
    }
   int score = -highPosition / Global::TILE_SIZE+7+bonus;
    mScoreText->setString("Score: " + std::to_string(score));
    mScoreText->setPosition(
        mView.getCenter().x + mView.getSize().x / 2.f - Global::TILE_SIZE,
        mView.getCenter().y - mView.getSize().y / 2.f
    );
}