#ifndef SELECT_PLAYER_STATE_HPP
#define SELECT_PLAYER_STATE_HPP

#include "../GUI/Container/Container.hpp"
#include "../State.hpp"

class SelectPlayerState : public State {
   public:
    SelectPlayerState(StateStack& stack, Context context, int selectState = 0);

    bool handleEvent(const sf::Event& event) override;
    bool update(sf::Time deltaTime) override;
    void updatePlayerChoiceSprite();
    void draw() override;

   private:
    sf::Text mTitleText;
    sf::Sprite mBackgroundSprite;
    sf::Sprite mPlayerChoiceSprite;
    GUI::Container mGUIContainer;

    int mChoiceCount;
    int mCurrentChoiceIndex;

    int mSelectState;
};

#endif
