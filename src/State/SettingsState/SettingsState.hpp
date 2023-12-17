#ifndef SETTINGS_STATE_HPP
#define SETTINGS_STATE_HPP

#include "../../GUI/Button/Button.hpp"
#include "../../GUI/Container/Container.hpp"
#include "../../Player/Player.hpp"
#include "../State.hpp"
#include "../../PlayerSettings/PlayerSettings.hpp"

class SettingsState : public State {
   public:
    SettingsState(StateStack& stack, Context context);
    void draw();
    bool update(sf::Time deltaTime);
    bool handleEvent(const sf::Event& event);

   private:
    void updateLabels();

    sf::Sprite mBackgroundSprite;
    GUI::Container mGUIContainer;

    std::array<GUI::Button::Ptr, static_cast<int>(Directions::ID::DirectionCount)> mBindingButtons;
    std::array<GUI::Label::Ptr, static_cast<int>(Directions::ID::DirectionCount)> mBindingLabels;
};

#endif
