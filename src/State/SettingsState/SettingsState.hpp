#ifndef SETTINGS_STATE_HPP
#define SETTINGS_STATE_HPP

#include "../../Player/Player.hpp"
#include "../../Utility/Utility.hpp"
#include "../GUI/Button/Button.hpp"
#include "../GUI/Container/Container.hpp"
#include "../GUI/Label/Label.hpp"
#include "../State.hpp"

class SettingsState : public State {
   public:
    SettingsState(StateStack& stack, Context context);

    void draw() override;
    bool update(sf::Time deltaTime) override;
    bool handleEvent(const sf::Event& event) override;

   private:
    PlayerSettings& mPlayerSettings;

    sf::Sprite mBackgroundSprite;
    GUI::Container mGUIContainer;

    std::array<
        GUI::Button::Ptr, static_cast<int>(Directions::ID::DirectionCount) +
                              PowerUp::Type::TypeButtonCount>
        mBindingButtons;
    std::array<
        GUI::Label::Ptr, static_cast<int>(Directions::ID::DirectionCount) +
                             PowerUp::Type::TypeButtonCount>
        mBindingLabels;

    void updateLabels();
    void addDirectionButtonLabel(
        Directions::ID direction, const sf::Vector2f& position,
        const std::string& text, Context context
    );
    void addPowerButtonLabel(
        PowerUp::Type power, const sf::Vector2f& position,
        const std::string& text, Context context
    );
};

#endif
