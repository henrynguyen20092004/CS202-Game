#include "Score.hpp"

#include "../Global/Global.hpp"

Score::Score(Player& player, sf::View& view, FontHolder& fontHolder)
    : mPlayer(player),
      mView(view),
      mInitialPlayerPosition(player.getPosition().y),
      mHighestPlayerPosition(mInitialPlayerPosition) {
    TextNode::Ptr textnode(new TextNode(fontHolder, "Score: 0", 40));
    mScoreText = textnode.get();
    attachChild(std::move(textnode));
}

void Score::addBonus() { mBonus += 1; }

void Score::updateCurrent(sf::Time deltaTime) {
    mHighestPlayerPosition =
        std::min(mPlayer.getPosition().y, mHighestPlayerPosition);
    int score =
        (mInitialPlayerPosition - mHighestPlayerPosition) / Global::TILE_SIZE +
        mBonus;

    mScoreText->setString("Score: " + std::to_string(score));
    mScoreText->setPosition(
        mView.getCenter().x + mView.getSize().x / 2.f - Global::TILE_SIZE,
        mView.getCenter().y - mView.getSize().y / 2.f + 20.f
    );
}
