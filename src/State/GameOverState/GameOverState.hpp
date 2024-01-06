#ifndef GAME_OVER_STATE_HPP
#define GAME_OVER_STATE_HPP

#include "../GUI/Container/Container.hpp"
#include "../State.hpp"

class GameOverState : public State {
   public:
    GameOverState(
        StateStack& stack, Context context, bool isMultiplayer = false,
        int deadPlayer = 0
    );

    bool handleEvent(const sf::Event& event) override;
    bool update(sf::Time deltaTime) override;
    void draw() override;

   private:
    sf::Text mGameOverText, mCurrentScoreText, mHighestScoreText, mWinnerText;
    sf::Time mElapsedTime;
    GUI::Container mGUIContainer;

    bool mIsMultiplayer;
    int mDeadPlayer;
};

#endif
