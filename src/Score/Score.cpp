#include "Score.hpp"

#include "../Global/Global.hpp"

Score::Score(Player& player, sf::View& view, FontHolder& fontHolder)
    : mPlayer(player),
      mView(view),
      mInitialPlayerPosition(player.getPosition().y),
      mHighestPlayerPosition(mInitialPlayerPosition) {
    TextNode::Ptr text(
        new TextNode(fontHolder, Fonts::ID::VTV323, "Score: 0", 40)
    );
    mScoreText = text.get();
    attachChild(std::move(text));
}

void Score::addBonus() { ++mBonus; }

void Score::updateCurrent(sf::Time deltaTime) {
    mHighestPlayerPosition =
        std::min(mPlayer.getPosition().y, mHighestPlayerPosition);
    Global::SCORE =
        (mInitialPlayerPosition - mHighestPlayerPosition) / Global::TILE_SIZE +
        mBonus;

    mScoreText->setText("Score: " + std::to_string(Global::SCORE));
    mScoreText->setPosition(
        mView.getCenter().x + mView.getSize().x / 2.f - 150.f,
        mView.getCenter().y - mView.getSize().y / 2.f + 10.f
    );
}
