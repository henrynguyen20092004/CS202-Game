#ifndef PAUSE_STATE_HPP
#define PAUSESTATE_HPP

#include "../../Identifier/Identifier.hpp"
#include "../State.hpp"

class PauseState : public State {
   public:
    PauseState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time deltaTime);
    virtual bool handleEvent(const sf::Event& event);

   private:
    sf::Sprite mBackgroundSprite;
    sf::Text mPausedText;
    sf::Text mInstructionText;
};

#endif
