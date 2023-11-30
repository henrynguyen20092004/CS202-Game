#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include "../State.hpp"

class MenuState : public State {
   public:
    MenuState(StateStack& stack, Context context);
    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

    void updateOptionText();

   private:
    enum OptionNames {
        Play,
        Exit,
    };

    sf::Sprite mBackgroundSprite;
    std::vector<sf::Text> mOptions;
    std::size_t mOptionIndex;
};

void centerOrigin(sf::Text& text);
void centerOrigin(sf::Sprite& sprite);

#endif
