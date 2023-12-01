#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

#include "../../Identifier/Identifier.hpp"
#include "../../Utility/Utility.hpp"
#include "../State.hpp"

class PauseState : public State {
   public:
    PauseState(StateStack& stack, Context context);

    void draw() override;
    bool update(sf::Time deltaTime) override;
    bool handleEvent(const sf::Event& event) override;

   private:
    sf::Sprite mBackgroundSprite;
    sf::Text mPausedText;
    sf::Text mInstructionText;
};

#endif
