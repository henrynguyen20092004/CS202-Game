#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include <cmath>

#include "../../Identifier/Identifier.hpp"
#include "../State.hpp"

class MenuState : public State {
   public:
    MenuState(StateStack& stack, Context context);
    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

    void updateOptionText();

   private:
    enum class OptionNames {
        Play,
        Exit,
    };

    sf::Sprite mBackgroundSprite;
    std::vector<sf::Text> mOptions;
    std::size_t mOptionIndex;
};

void centerOrigin(sf::Text& text);
void centerOrigin(sf::Sprite& sprite);
#endif  // MENUSTATE_HPP
