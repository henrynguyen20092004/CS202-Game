#ifndef HIGH_SCORE_STATE_HPP
#define HIGH_SCORE_STATE_HPP

#include "../../HighScore/HighScore.hpp"
#include "../GUI/Container/Container.hpp"
#include "../State.hpp"

class HighScoreState : public State {
   public:
    HighScoreState(StateStack& stack, Context context);

    bool handleEvent(const sf::Event& event) override;
    bool update(sf::Time deltaTime) override;
    void draw() override;

   private:
    sf::Sprite mBackgroundSprite, mFrameSprite;
    GUI::Container mGUIContainer;

    HighScore* mHighScore;
    sf::Text mTitleText;
    std::vector<sf::Text> mTexts;

    void setText(sf::Vector2f windowSize);
};

#endif
