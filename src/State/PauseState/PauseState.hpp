#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

#include "../GUI/Container/Container.hpp"
#include "../State.hpp"

class PauseState : public State {
   public:
    PauseState(StateStack& stack, Context context);

    bool handleEvent(const sf::Event& event) override;
    bool update(sf::Time deltaTime) override;
    void draw() override;

   private:
    sf::Sprite mBackgroundSprite;
    sf::Text mPausedText;
    GUI::Container mGUIContainer;
};

#endif
