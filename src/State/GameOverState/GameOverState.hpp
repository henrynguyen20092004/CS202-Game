#ifndef GAME_OVER_STATE_HPP
#define GAME_OVER_STATE_HPP

#include "../GUI/Container/Container.hpp"
#include "../State.hpp"

class GameOverState : public State {
   public:
    GameOverState(StateStack& stack, Context context);

    bool handleEvent(const sf::Event& event) override;
    bool update(sf::Time deltaTime) override;
    void draw() override;

   private:
    sf::Text mGameOverText;
    sf::Text mCurrentScoreText;
    sf::Text mHighestScoreText;
    sf::Time mElapsedTime;
    GUI::Container mGUIContainer;
};
#endif
