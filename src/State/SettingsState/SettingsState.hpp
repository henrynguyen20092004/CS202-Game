#ifndef SETTINGS_STATE_HPP
#define SETTINGS_STATE_HPP

#include "../../Player/Player.hpp"
#include "../../PlayerSettings/PlayerSettings.hpp"
#include "../../PowerUpSettings/PowerUpSettings.hpp"
#include "../../Utility/Utility.hpp"
#include "../GUI/Button/Button.hpp"
#include "../GUI/Container/Container.hpp"
#include "../GUI/Label/Label.hpp"
#include "../State.hpp"

class SettingsState : public State {
   public:
    SettingsState(StateStack& stack, Context context);
    void draw();
    bool update(sf::Time deltaTime);
    bool handleEvent(const sf::Event& event);

   private:
    PlayerSettings& mPlayerSettings;

    sf::Sprite mBackgroundSprite;
    GUI::Container mGUIContainer;

    std::array<
        GUI::Button::Ptr, static_cast<int>(Directions::ID::DirectionCount) +
                              static_cast<int>(PowerUp::Type::TypeButtonCount)>
        mBindingButtons;
    std::array<
        GUI::Label::Ptr, static_cast<int>(Directions::ID::DirectionCount) +
                             static_cast<int>(PowerUp::Type::TypeButtonCount)>
        mBindingLabels;

    void updateLabels();
    void addDirButtonLabel(
        Directions::ID direction, const sf::Vector2f& position,
        const std::string& text, Context context
    );
    void addPowButtonLabel(
        PowerUp::Type power, const sf::Vector2f& position,
        const std::string& text, Context context
    );
};

#endif
