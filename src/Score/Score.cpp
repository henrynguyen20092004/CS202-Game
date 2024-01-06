#include "Score.hpp"

#include "../Global/Global.hpp"

Score::Score(Player& player, sf::View& worldView, FontHolder& fontHolder)
    : mPlayer(player), mWorldView(worldView) {
    TextNode::Ptr text(
        new TextNode(fontHolder, Fonts::ID::VTV323, "Score: 0", 40)
    );
    mScoreText = text.get();
    attachChild(std::move(text));
}

void Score::init() {
    mInitialPlayerPosition = mPlayer.getWorldPosition().y;
    mHighestPlayerPosition = mInitialPlayerPosition;
}

void Score::addBonus() { mBonus++; }

void Score::updateCurrent(sf::Time deltaTime) {
    mHighestPlayerPosition =
        std::min(mPlayer.getWorldPosition().y, mHighestPlayerPosition);
    Global::SCORE =
        (mInitialPlayerPosition - mHighestPlayerPosition) / Global::TILE_SIZE +
        mBonus;

    mScoreText->setText("Score: " + std::to_string(Global::SCORE));
    mScoreText->setPosition(
        mWorldView.getCenter().x + mWorldView.getSize().x / 2.f -
            mScoreText->getTextSize() - 20.f,
        mWorldView.getCenter().y - mWorldView.getSize().y / 2.f + 10.f
    );
}

void Score::saveCurrent(std::ofstream& fout) const {
    SceneNode::saveCurrent(fout);
    fout << mInitialPlayerPosition << ' ' << mBonus << '\n';
}

void Score::loadCurrent(std::ifstream& fin) {
    SceneNode::loadCurrent(fin);
    fin >> mInitialPlayerPosition >> mBonus;
}
