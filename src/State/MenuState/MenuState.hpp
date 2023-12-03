#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include "../GUI/Container/Container.hpp"
#include "../State.hpp"

class MenuState : public State {
   public:
    MenuState(StateStack& stack, Context context);
    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

   private:
    sf::Sprite mBackgroundSprite;

    GUI::Container mGUIContainer;
};

#endif
