#ifndef TITLE_STATE_HPP
#define TITLE_STATE_HPP

#include "../State.hpp"

class TitleState : public State {
   public:
    TitleState(StateStack& stack, Context context);
    void draw() override;
    bool update(sf::Time deltaTime) override;
    bool handleEvent(const sf::Event& event) override;

   private:
    sf::Sprite mBackgroundSprite;
    sf::Text mText;
    bool mShowText;
    sf::Time mTextEffectTime;
};

#endif
