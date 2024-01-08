#ifndef SELECT_PLAYER_STATE_HPP
#define SELECT_PLAYER_STATE_HPP

#include "../GUI/Container/Container.hpp"
#include "../State.hpp"

class SelectPlayerState : public State {
   public:
    enum Type {
        Player1Single,
        Player1Multi,
        Player2Multi,
    };

    SelectPlayerState(
        StateStack& stack, Context context, SelectPlayerState::Type selectState
    );

    bool handleEvent(const sf::Event& event) override;
    bool update(sf::Time deltaTime) override;
    void draw() override;

   private:
    sf::Text mTitleText;
    sf::Sprite mBackgroundSprite, mPlayerChoiceSprite;
    GUI::Container mDirectionButtonsContainer, mGUIContainer;

    int mChoiceCount, mCurrentChoiceIndex, mSelectState;

    void updatePlayerChoiceSprite();
};

#endif
