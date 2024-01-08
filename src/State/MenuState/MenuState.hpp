#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include "../GUI/Container/Container.hpp"
#include "../State.hpp"

class MenuState : public State {
   public:
    MenuState(StateStack& stack, Context context);

    virtual bool handleEvent(const sf::Event& event) override;
    virtual bool update(sf::Time deltaTime) override;
    virtual void draw() override;

   private:
    sf::Sprite mBackgroundSprite;
    sf::Text mTitleText;
    GUI::Container mGUIContainer;
};

#endif
